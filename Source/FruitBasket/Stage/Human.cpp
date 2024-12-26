// Fill out your copyright notice in the Description page of Project Settings.

#include "Human.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimSequence.h"

// Sets default values
AHuman::AHuman()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// skeltalmesh
	HumanMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Human Mesh"));
	RootComponent = HumanMesh;

    // trigger
    Trigger->SetupAttachment(HumanMesh);

    // audio
    Audio->SetupAttachment(HumanMesh);

	// collider
	BodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Body Collider"));
	BodyCollider->SetupAttachment(HumanMesh);
	BodyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BodyCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

}

// Called when the game starts or when spawned
void AHuman::BeginPlay()
{
	Super::BeginPlay();
	
	HumanMesh->PlayAnimation(Anim, true);
}

// Called every frame
void AHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
