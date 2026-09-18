// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImportJSONToPiano.generated.h"

UCLASS()
class HOUSEEDWARDS_API UImportJSONToPiano : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Piano|Import")
	static bool ImportSongFromJson(const FString& JsonFilePath, const FString& AssetName, const FString& AssetPath);
#endif
};
