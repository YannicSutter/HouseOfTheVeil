// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPuzzleManager.h"

// Sets default values
AChessPuzzleManager::AChessPuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChessPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
