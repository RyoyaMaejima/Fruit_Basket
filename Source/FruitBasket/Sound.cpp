// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound.h"
#include "Components/AudioComponent.h"

// Sets default values
ASound::ASound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// audio
    Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	RootComponent = Audio;
}

// Called when the game starts or when spawned
void ASound::BeginPlay()
{
	Super::BeginPlay();
	
	PlayBGM();
}

// Called every frame
void ASound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASound::PlayBGM()
{
	if (Audio == nullptr)
	{
		return;
	}

	Audio->SetSound(BGM);
	Audio->Play();
}