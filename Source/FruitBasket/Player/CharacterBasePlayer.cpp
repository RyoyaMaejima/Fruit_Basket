// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "CharacterBasePlayer.h"
#include <algorithm>

// Sets default values
ACharacterBasePlayer::ACharacterBasePlayer()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // コントローラの回転をキャラクタに適用
    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    // Spring Armでカメラの位置を指定
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    // Spring Armに取り付けるCamera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // ######################
    // Static Mesh Component
    // ######################
    // StaticMeshComponentをスケルタルメッシュコンポーネントの代わりに指定する
    // Create StaticMeshComponent
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    // Attach StaticMeshComponent to the root component
    StaticMeshComponent->SetupAttachment(RootComponent);
    // Disable the default skeletal mesh component
    GetMesh()->SetVisibility(false, true);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 当たり判定
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    CapsuleComp->SetupAttachment(RootComponent);
    CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBasePlayer::OnCapsuleBeginOverlap);
}

// Called when the game starts or when spawned
void ACharacterBasePlayer::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACharacterBasePlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 地面設置のチェック -> ジャンプ回数リセット
    if (GetCharacterMovement()->IsMovingOnGround())
    {
        // ジャンプ回数をリセット
        JumpCount = 0;
    }
}

// Called to bind functionality to input
void ACharacterBasePlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Move forward/backward
    PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBasePlayer::MoveForward);

    // Move right/left
    PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBasePlayer::MoveRight);

    // Turn LookUp
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACharacterBasePlayer::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacterBasePlayer::LookUp);

    // Simple Jump
    PlayerInputComponent->BindAction("SimpleJump", IE_Pressed, this, &ACharacterBasePlayer::StartJump);
    PlayerInputComponent->BindAction("SimpleJump", IE_Released, this, &ACharacterBasePlayer::StopJump);
}

void ACharacterBasePlayer::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // 前方ベクトルを取得
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 前方ベクトルを計算
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ACharacterBasePlayer::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // 右方向ベクトルを取得
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 右方向ベクトルを計算
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ACharacterBasePlayer::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ACharacterBasePlayer::LookUp(float Value)
{
    if (SpringArm)
    {
        FRotator NewRotation = SpringArm->GetRelativeRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this), -MaxLookUp, MaxLookUp);
        SpringArm->SetRelativeRotation(NewRotation);
    }
}

void ACharacterBasePlayer::StartJump()
{
    bPressedJump = true;
    GetCharacterMovement()->JumpZVelocity = jumpImpulse;

    // // 重力の方向を取得
    // FVector gravityDirection = GetGravityDirection();

    // // 重力の方向を正規化して、逆向きにjumpImpulseの方向を計算
    // FVector JumpImpulse = -gravityDirection.GetSafeNormal() * jumpImpulse;

    // // jumpさせる
    // GetCharacterMovement()->AddImpulse(JumpImpulse, true);
}

void ACharacterBasePlayer::StopJump()
{
    bPressedJump = false;
}

// プレイヤの当たり判定
void ACharacterBasePlayer::OnCapsuleBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // UKismetSystemLibrary::PrintString(GEngine->GetWorld(), "hello");
        // UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());
    }
}