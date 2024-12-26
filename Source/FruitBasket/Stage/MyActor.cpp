// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // trigger
    Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger"));

    // audio
    Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor *AMyActor::GetAcceptableActor(FName AcceptableActorTag) const
{
    TArray<AActor*> Actors;
    Trigger->GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
        if (HasAcceptableTag)
        {
            return Actor;
        }
    }
    return nullptr;
}

void AMyActor::GetAcceptableActors(FName AcceptableActorTag, TArray<AActor*>* OverlapActors)
{
    TArray<AActor*> Actors;
    Trigger->GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
        if (HasAcceptableTag)
        {
            OverlapActors->Add(Actor);
        }
    }
}

void AMyActor::PlaySE(USoundWave* SE)
{
    if (SE == nullptr)
    {
        return;
    }

    // SEを鳴らす
    Audio->SetSound(SE);
    Audio->Play();
}
