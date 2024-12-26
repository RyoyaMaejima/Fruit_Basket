// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

#include "BasketPlayer.h"

// Sets default values
ABasketPlayer::ABasketPlayer()
{

    // ###############
    // BasketPlayer
    // ###############

    // Spring Armでカメラの位置を指定
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    // Spring Armに取り付けるCamera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ABasketPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABasketPlayer::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABasketPlayer::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABasketPlayer::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABasketPlayer::LookUp);
    // PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABasketPlayer::Turn);
    PlayerInputComponent->BindAxis(TEXT("Jump"), this, &ABasketPlayer::Jump);
}

void ABasketPlayer::MoveForward(float Value)
{

    // 移動ベクトル
    FVector DeltaLocation = FVector(Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f, 0.f);

    // local方向にdeltaLocationの値だけ、Tankを進める
    AddActorLocalOffset(DeltaLocation, true);

    // // 現在の回転を取得
    // FRotator currentBaseMeshRotation = BaseMesh->GetRelativeRotation();
    // if (currentBaseMeshRotation.Yaw != 0.f)
    // {
    //     if (currentBaseMeshRotation.Yaw > 0)
    //     {
    //         BaseMesh->SetRelativeRotation(FRotator(0.f, currentBaseMeshRotation.Yaw - Value * TurnRateMoving * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f));
    //     }
    //     else
    //     {
    //         BaseMesh->SetRelativeRotation(FRotator(0.f, currentBaseMeshRotation.Yaw + Value * TurnRateMoving * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f));
    //     }
    //     // Yawが0.01以下ならば0にセットする
    //     if (FMath::Abs(currentBaseMeshRotation.Yaw) < 0.1)
    //     {
    //         BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    //     }
    // }

    // // FRotator cameraRotation = Camera->GetComponentRotation();
    // // SetActorRotation(FRotator(0.f, cameraRotation.Yaw, 0.f));
}

void ABasketPlayer::MoveRight(float Value)
{

    // 移動
    FVector DeltaLocation = FVector(0.f, Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f);

    // local方向にdeltaLocationの値だけ、Tankを進める
    AddActorLocalOffset(DeltaLocation, true);

    // // rootcomponent回転
    // SetRotation(FRotator(0.f, 90 * Value, 0.f));

    // // mesh回転
    // // BaseMeshの現在の回転を取得
    // // FRotator currentBaseMeshRotation = ;
    // playerRotation = BaseMesh->GetRelativeRotation();
    // if (FMath::Abs(Value) < 0.01)
    // {
    //     BaseMesh->SetRelativeRotation(playerRotation);
    // }
    // else
    // {
    //     // BaseMesh->SetRelativeRotation(FRotator(0.f, FMath::Clamp(playerRotation.Yaw + Value * TurnRateMoving * UGameplayStatics::GetWorldDeltaSeconds(this), -90.0f, 90.0f), 0.f));
    //     BaseMesh->SetRelativeRotation(FRotator(0.f, 90 * Value, 0.f));
    //     playerRotation = BaseMesh->GetRelativeRotation();
    // }

    // AddActorLocalRotation(FRotator(0.f, FMath::Clamp(currentBaseMeshRotation.Yaw + Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this), -90.0f, 90.0f), 0.f));
}

void ABasketPlayer::Turn(float Value)
{
    // 回転
    FRotator DeltaRotation = FRotator::ZeroRotator;

    // Yaw = Value * DeltaTime * TurnRate
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

void ABasketPlayer::LookUp(float Value)
{
    if (SpringArm)
    {
        FRotator NewRotation = SpringArm->GetRelativeRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this), -80.0f, 80.0f); // 制限をかけることも可能
        SpringArm->SetRelativeRotation(NewRotation);
    }

    // // 回転
    // FRotator DeltaRotation = FRotator::ZeroRotator;

    // // Yaw = Value * DeltaTime * TurnRate
    // DeltaRotation.Pitch = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    // AddActorLocalRotation(DeltaRotation, true);
}

void ABasketPlayer::Jump(float Value)
{
    // jump direction
    FVector JumpDirection = FVector(0, 0, jumpImpulse * Value);

    // AddActorLocalOffset(JumpDirection);
    // AddImpulse(JumpDirection);
    BaseMesh->AddImpulse(JumpDirection, TEXT("NONE"), true);
}
