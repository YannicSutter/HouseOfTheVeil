// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UPianoSongData.h"
#include "PianoController.generated.h"

UCLASS()
class HOUSEEDWARDS_API APianoController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APianoController();

	UPROPERTY(EditAnywhere, Category="Playback") UUPianoSongData* SongData;
	UPROPERTY(EditAnywhere, Category="Playback") class USoundWave* Audio;
	UPROPERTY(EditAnywhere, Category="Playback") float StartOffset = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Keys") TArray<UStaticMeshComponent*> KeyComponent;	

	UPROPERTY(EditAnywhere, Category="Anim") float PressAngleDeg = 6.f;
	UPROPERTY(EditAnywhere, Category="Anim") float PressSpeed = 18.f;
	UPROPERTY(EditAnywhere, Category="Anim") float ReleaseSpeed = 24.f;
	UPROPERTY(EditAnywhere, Category="Anim") FVector PressAxis = FVector(1, 0, 0);
	double PlaybackStartTime = 0.f;

	UFUNCTION(BlueprintCallable, Category = "Piano")
	void StartPlayback();

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY() class UAudioComponent* AudioComp;

	struct FActiveNote { int32 Midi; float OffTime; float Vel;};
	TArray<FActiveNote> Active;
	int32 NextNoteIdx = 0;

	bool bIsPlaying = false;

	TArray<float> TargetAngle;
	TArray<float> CurrentAngle;

	int32 MidiToIndex(int32 Midi) const { return Midi - 21; }
	void PressKey(int32 Midi, float Velocity);
	void ReleaseKey(int32 Midi);
	void UpdateKeyVisuals(float DeltaSeconds);

	void StopPlayback();

};