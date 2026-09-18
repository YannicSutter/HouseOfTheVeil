// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UPianoSongData.generated.h"

USTRUCT(BlueprintType)
struct FNoteEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Midi = 60;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Time = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Duration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Velocity = 1.0f;
};

UCLASS(Blueprintable)
class HOUSEEDWARDS_API UUPianoSongData : public UDataAsset
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString SongTitle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float TotalLengthSec = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FNoteEvent> Notes;	
};
