
#include "PianoController.h"
#include "Components/AudioComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

static FString MidiToNoteName(int32 Midi)
{
	static const TCHAR* Names[12] = { TEXT("C"), TEXT("C#"), TEXT("D"), TEXT("D#"), TEXT("E"), TEXT("F"), TEXT("F#"), TEXT("G"), TEXT("G#"), TEXT("A"), TEXT("A#"), TEXT("B") };
	const int32 n = Midi % 12;
	const int32 octave = (Midi / 12) - 1; // MIDI 60 => C4
	return FString::Printf(TEXT("%s%d"), Names[n], octave);
}
// Sets default values
APianoController::APianoController()
{ 	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void APianoController::BeginPlay()
{
	Super::BeginPlay();

	bIsPlaying = false;

	SetActorTickEnabled(true);
	
	TargetAngle.SetNum(88); CurrentAngle.SetNum(88);
	for (int i=0; i<88; ++i) { TargetAngle[i] = 0.f; CurrentAngle[i] = 0.f; }

	//Set AudioComponent 
	AudioComp = NewObject<UAudioComponent>(this);
	AudioComp->bAutoActivate = false;
	AudioComp->bIsUISound = false;
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->RegisterComponent();
	AudioComp->SetSound(Audio);

	Active.Reset();
	NextNoteIdx = 0;

	if (AudioComp)
	{
		AudioComp->Stop();
	}
}

// Called every frame
void APianoController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsPlaying) return;
	//if (!SongData || !AudioComp) return;
	if (!SongData) return;

	const float T = (GetWorld()->GetTimeSeconds() - PlaybackStartTime) + StartOffset;

	// Note-On
	const TArray<FNoteEvent>& N = SongData->Notes;
	while (NextNoteIdx < N.Num() && N[NextNoteIdx].Time <= T)
	{
		const FNoteEvent& E = N[NextNoteIdx++];
		const int32 Idx = MidiToIndex(E.Midi);
		PressKey(E.Midi, E.Velocity);
		Active.Add({ E.Midi, E.Time + E.Duration, E.Velocity });

		//UE_LOG(LogTemp, Log, TEXT("[Piano] Press  MIDI=%d (%s)  Idx=%d  T=%.3fs  vel=%.2f"),
		//	   E.Midi, *MidiToNoteName(E.Midi), Idx, T, E.Velocity);

		//if (GEngine)
		//{
		//	const FString Msg = FString::Printf(TEXT("Press %s (MIDI %d)  Idx %d  T=%.2f"),
		//										*MidiToNoteName(E.Midi), E.Midi, Idx, T);
		//	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, Msg);
		//}
	}

	// Note-Off
	for (int32 i = Active.Num()-1; i >= 0; --i)
	{
		if (Active[i].OffTime <= T)
		{
			ReleaseKey(Active[i].Midi);
			Active.RemoveAtSwap(i);
		}
	}

	// Visuals
	UpdateKeyVisuals(DeltaSeconds);

	bool bNoMoreNotes = (NextNoteIdx >= SongData->Notes.Num());
	bool bNoActiveKeys = (Active.Num() == 0);

	if (bNoMoreNotes && bNoActiveKeys)
	{
		StopPlayback();
		UE_LOG(LogTemp, Warning, TEXT("[Piano] Cannot start playback - missing Song data"));
	}

}

void APianoController::StartPlayback()
{
		
	//if (!SongData || !AudioComp || !Audio)
	if (!SongData)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Piano] Cannot start playback - missing Song data"));
		return;
	}

	SetActorTickEnabled(true);
	bIsPlaying = true;
	PlaybackStartTime = GetWorld()->GetTimeSeconds();
	
	// Reset state
	Active.Reset();
	NextNoteIdx = 0;

	for (int32 i = 0; i < 88; ++i)
	{
		TargetAngle[i] = 0.f;
		CurrentAngle[i] = 0.f;
	}

	// Restart audio
	//AudioComp->Stop();
	//AudioComp->SetSound(Audio);
	//AudioComp->Play(StartOffset);	
}

void APianoController::PressKey(int32 Midi, float Velocity)
{
	const int32 idx = MidiToIndex(Midi);
	if (idx < 0 || idx >= 88) return;
	
	const float v = FMath::Clamp(Velocity, 0.f, 1.0f);
	TargetAngle[idx] = PressAngleDeg * (0.7);
	//TargetAngle[idx] = PressAngleDeg * (0.5f + 0.5f * v);
}

void APianoController::ReleaseKey(int32 Midi)
{
	const int32 idx = MidiToIndex(Midi);
	if (idx < 0 || idx >= 88) return;
	TargetAngle[idx] = 0.f;
}

void APianoController::UpdateKeyVisuals(float DeltaSeconds)
{	
	for (int32 i=0;i<88;++i)
	{
		const float speed = (TargetAngle[i] > CurrentAngle[i]) ? PressSpeed : ReleaseSpeed;
		CurrentAngle[i] = FMath::FInterpConstantTo(CurrentAngle[i], TargetAngle[i], DeltaSeconds, speed);
		//if (AActor* Key = (KeyActors.IsValidIndex(i) ? KeyActors[i] : nullptr))
		if (TArray<UStaticMeshComponent*>::ElementType Key = (KeyComponent.IsValidIndex(i) ? KeyComponent[i] : nullptr))
		{			
			FTransform Tr = Key->GetComponentTransform();			
			
			FRotator R(0,0,0);
			R.Roll  = (PressAxis.X>0) ? CurrentAngle[i] : 0;
			R.Pitch = (PressAxis.Y>0) ? CurrentAngle[i] : 0;
			R.Yaw   = (PressAxis.Z>0) ? CurrentAngle[i] : 0;
			Key->SetRelativeRotation(R);
			
		}		
	}
}

void APianoController::StopPlayback()
{
	bIsPlaying = false;
	Active.Reset();

	for (int32 i = 0; i < 88; ++i)
	{
		TargetAngle[i] = 0.f;
		CurrentAngle[i] = 0.f;
	}

	if (AudioComp) AudioComp->Stop();

	UE_LOG(LogTemp, Warning, TEXT("[Piano] Playback finished"))
}