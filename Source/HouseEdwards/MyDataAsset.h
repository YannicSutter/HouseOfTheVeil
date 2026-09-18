// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyDataAsset.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMyDataItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
};

UCLASS()
class HOUSEEDWARDS_API UMyDataAsset : public UDataAsset
{
	GENERATED_BODY()

	public:	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMyDataItem> MyData;
	
};
