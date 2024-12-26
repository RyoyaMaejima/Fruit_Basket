// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"

#include "BasePlayer.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // collider
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComp;
    // meshを用意
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComp);
    // RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// // Called to bind functionality to input
// void ABasePlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
// {
//     Super::SetupPlayerInputComponent(PlayerInputComponent);
// }
