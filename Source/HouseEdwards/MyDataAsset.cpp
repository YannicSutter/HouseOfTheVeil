// Fill out your copyright notice in the Description page of Project Settings. blabla

#include "MyDataAsset.h"
#include "UPianoSongData.h"
#include "Misc/FileHelper.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h" 

#if WITH_EDITOR
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "Factories/DataAssetFactory.h"
#include "Modules/ModuleManager.h"
#endif


#if WITH_EDITOR
bool ImportJsonToUPianoSongData(const FString& JsonFilePathIn, const FString& AssetName, const FString& AssetPath)
{
	FString JsonPath = JsonFilePathIn;
	
	JsonPath = JsonPath.TrimStartAndEnd();
	JsonPath = JsonPath.Replace(TEXT("\""), TEXT(""));
	
	JsonPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	
	FPaths::NormalizeFilename(JsonPath);

	UE_LOG(LogTemp, Log, TEXT("Import called with Path='%s'  AssetName='%s'  AssetPath='%s'"),
		   *JsonPath, *AssetName, *AssetPath);
	
	if (!FPaths::FileExists(JsonPath))
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *JsonPath);
		return false;
	}
	
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *JsonPath, FFileHelper::EHashOptions::None, FILEWRITE_None))
	{		
		if (!FFileHelper::LoadFileToString(JsonString, *JsonPath, FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Error, TEXT("LoadFileToString failed: %s"), *JsonPath);
			return false;
		}
	}

	TSharedPtr<FJsonObject> Root;
	auto Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Bad JSON")); return false;
	}

	//FString Title = Root->GetStringField(TEXT("Title"));
	FString Title;
	if (!Root->TryGetStringField(TEXT("Title"), Title))
	{
		Root->TryGetStringField(TEXT("title"), Title); 
	}
	
	float Length = 0.0f;
	if (Root->HasTypedField<EJson::Number>(TEXT("duration"))) { Length = Root->GetNumberField(TEXT("duration")); }

	const TArray<TSharedPtr<FJsonValue>>* Tracks=nullptr;
	if (!Root->TryGetArrayField(TEXT("tracks"), Tracks))
	{ UE_LOG(LogTemp, Error, TEXT("No 'tracks'")); return false; }

	TArray<FNoteEvent> Parsed;

	for (const auto& TrackVal : *Tracks)
	{
		const TSharedPtr<FJsonObject> TrackObj = TrackVal->AsObject();
		if (!TrackObj) continue;

		const TArray<TSharedPtr<FJsonValue>>* Notes=nullptr;
		if (!TrackObj->TryGetArrayField(TEXT("notes"), Notes)) continue;

		for (const auto& NoteVal : *Notes)
		{
			const TSharedPtr<FJsonObject> N = NoteVal->AsObject(); if (!N) continue;
			FNoteEvent E;
			E.Midi     = (int32)N->GetIntegerField(TEXT("midi"));
			E.Time     = (float)N->GetNumberField(TEXT("time"));
			E.Duration = (float)N->GetNumberField(TEXT("duration"));
			E.Velocity = (float)N->GetNumberField(TEXT("velocity"));
			Parsed.Add(E);
			Length = FMath::Max(Length, E.Time + E.Duration);
		}
	}

	Parsed.StableSort([](const FNoteEvent& A, const FNoteEvent& B){ return A.Time < B.Time; });

	// Asset anlegen
	UDataAssetFactory* Factory = NewObject<UDataAssetFactory>();
	Factory->DataAssetClass = UUPianoSongData::StaticClass();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	UObject* NewAsset = AssetTools.CreateAsset(AssetName, AssetPath, UUPianoSongData::StaticClass(), Factory);

	if (UUPianoSongData* Song = Cast<UUPianoSongData>(NewAsset))
	{
		Song->SongTitle = Title;
		Song->TotalLengthSec = Length;
		Song->Notes = MoveTemp(Parsed);
		Song->MarkPackageDirty();
		UE_LOG(LogTemp, Log, TEXT("Created Song asset: %s/%s (%d notes)"), *AssetPath, *AssetName, Song->Notes.Num());
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Asset creation failed"));
	return false;
}

#endif