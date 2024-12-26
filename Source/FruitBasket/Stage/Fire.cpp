// Fill out your copyright notice in the Description page of Project Settings.

#include "Fire.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // mesh
    FireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
    RootComponent = FireMesh;

    // trigger
    Trigger->SetupAttachment(FireMesh);

    // audio
    Audio->SetupAttachment(FireMesh);

	// emitter
    FireEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Emitter"));
    FireEmitter->SetupAttachment(FireMesh);
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TArray<AActor *> OverlapActors;

    GetAcceptableActors(WoodTag, &OverlapActors);

    // 範囲内にある木を燃やす
    BurnWoods(OverlapActors);
}

void AFire::BurnWoods(TArray<AActor *> OverlapActors)
{
    if (OverlapActors.Num() < 1)
    {
        return;
    }

    // 木を削除する
    for (AActor* OverlapActor : OverlapActors)
    {
        OverlapActor->Destroy();
    }

    // 燃える音を鳴らす
    PlaySE(BurnSE);
}
