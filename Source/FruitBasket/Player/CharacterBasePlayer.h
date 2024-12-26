// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBasePlayer.generated.h"

UCLASS()
class FRUITBASKET_API ACharacterBasePlayer : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACharacterBasePlayer();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Staitic Mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
    class UStaticMeshComponent *StaticMeshComponent;

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

    // Playerの回転速度
    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnRate = 45.f;

    // カメラの縦移動の制限角度
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxLookUp = 80.f;

    // jump
    UPROPERTY(EditAnywhere, Category = "Movement")
    float jumpImpulse = 500.f;

    // 最大ジャンプ回数
    UPROPERTY(EditAnywhere, Category = "Jump")
    int MaxJumpCount = 3;

    // 現在のジャンプ回数
    UPROPERTY(EditAnywhere, Category = "Jump")
    int JumpCount = 0;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // Move forward/backward
    void MoveForward(float Value);

    // Move right/left
    void MoveRight(float Value);

    void Turn(float Value);
    void LookUp(float Value);

    // ###########
    // jump
    // ############
    // Simple Jump
    void StartJump();
    void StopJump();

    // ##############
    // respawn判定
    // #############
    UFUNCTION()
    void OnCapsuleBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
    UPROPERTY(VisibleAnywhere)
    class UCapsuleComponent *CapsuleComp;
};
