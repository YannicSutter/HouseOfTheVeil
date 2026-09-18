// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportJSONToPiano.h"

#if WITH_EDITOR
bool ImportJsonToUPianoSongData(const FString& JsonFilePath, const FString& AssetName, const FString& AssetPath);

bool UImportJSONToPiano::ImportSongFromJson(const FString& JsonFilePath, const FString& AssetName, const FString& AssetPath)
{
	return ImportJsonToUPianoSongData(JsonFilePath, AssetName, AssetPath);
}
#endif
