// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "BasketPlayer.generated.h"

UCLASS()
class FRUITBASKET_API ABasketPlayer : public ABasePlayer
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABasketPlayer();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // スプリングアーム
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USpringArmComponent *SpringArm;

    // カメラ
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCameraComponent *Camera;

    // ##################
    // Moving Platform
    // ##################
    // Ballのspeed
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Speed = 200.f;

    // Ballの回転速度
    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnRate = 45.f;

    // 移動の横向きになる時の速度 or 移動の立向きに戻る時の速度
    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnRateMoving = 100.f;

    // jump
    UPROPERTY(EditAnywhere, Category = "Movement")
    float jumpImpulse = 500.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    bool canJump = false;

    // 現在のMeshの回転を保持
    UPROPERTY(EditAnywhere, Category = "Movement")
    FRotator playerRotation = FRotator(0.f, 0.f, 0.f);

    // 移動関数
    void MoveForward(float Value);
    void MoveRight(float Value);
    // void Turn(float Value);

    // カメラによる視点変更
    // 横方向アングル
    void Turn(float Value);
    // 縦方向アングル
    void LookUp(float Value);

    // jump
    void Jump(float Value);
};