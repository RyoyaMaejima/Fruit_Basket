// Fill out your copyright notice in the Description page of Project Settings.

#include "Dog.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADog::ADog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// skeltalmesh
	DogMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Dog Mesh"));
	RootComponent = DogMesh;

    // trigger
    Trigger->SetupAttachment(DogMesh);

    // audio
    Audio->SetupAttachment(DogMesh);

	// collider
	BodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Body Collider"));
	BodyCollider->SetupAttachment(DogMesh);
	BodyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BodyCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	FaceCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Face Collider"));
	FaceCollider->SetupAttachment(DogMesh);
	FaceCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    FaceCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ADog::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AActor *Actor = GetAcceptableActor(FruitTag);

	// 目的地に到着したか
	if (IsArrivePoint(DeltaTime))
	{
		IsTurn = true;
	}
	// フルーツと接触したとき
	else if (Actor != nullptr)
	{
		// 既に咥えているときは咥えられない
		if (!IsFruit)
		{
			Fruit = Cast<AFruit>(Actor);
			// プレイヤーのカゴに入っていなければ咥える
			if (!Fruit->GetIsGet())
			{
				IsEat = true;
			}
		}
	}

	// ターン
	if (IsTurn)
	{
		Turn(DeltaTime);
	}
	// 咥える
	else if (IsEat)
	{
		Eat(DeltaTime);
	}
	// 移動
	else
	{
		Walk(DeltaTime);
	}

	// フルーツを咥えているときはアニメーションに合わせてフルーツを動かす
	if (IsFruit)
	{
		MoveFruit();
	}
}

void ADog::Walk(float DeltaTime)
{
	if (MovePoints.Num() < 2 || WalkAnim == nullptr)
	{
		return;
	}

	if (!WalkAnimFlag)
	{
		// アニメーションを設定
		DogMesh->PlayAnimation(WalkAnim, true);
		WalkAnimFlag = true;
	}

	// 移動方向を設定
	FVector CurrentLocation = GetActorLocation();
	FVector GoalLocation = MovePoints[PointNum];
	FVector MoveDirection = GoalLocation - CurrentLocation;
	MoveDirection = MoveDirection.GetSafeNormal();

	// 移動
	FVector MovePos = CurrentLocation + (Speed * DeltaTime) * MoveDirection;
	SetActorLocation(MovePos);
}

void ADog::Turn(float DeltaTime)
{
	if (MovePoints.Num() < 2 || TurnRightAnim == nullptr || TurnLeftAnim == nullptr)
	{
		return;
	}

	if (!TurnAnimFlag)
	{
		PointNum++;
		// 最後のポイントに到着したら最初のポイントに戻る
		if (PointNum >= MovePoints.Num())
		{
			PointNum = 0;
		}

		UAnimationAsset* TurnAnim;

		if (IsGoalRight())
		{
			TurnAnim = TurnRightAnim;
			TurnAngle = 90.f;
		}
		else
		{
			TurnAnim = TurnLeftAnim;
			TurnAngle = -90.f;
		}

		// アニメーションを設定
		DogMesh->PlayAnimation(TurnAnim, true);
		WalkAnimFlag = false;
		TurnAnimFlag = true;

		// アニメーションを開始
		AnimTimer = 0.f;

		// アニメーション通知時刻を取得
		AnimNotifyTimes(TurnAnim);

		// 現在の回転角度を取得
		CurrentRotation = GetActorRotation();
	}

	AnimTimer += DeltaTime;

	// アニメーションの途中で方向転換を行う
	if (AnimTimer >= AnimNotifyTime && AnimTimer <= AnimFinishTime)
	{
		float theta = TurnAngle / (AnimFinishTime - AnimNotifyTime) * (AnimTimer - AnimNotifyTime);
		FRotator Rotation = CurrentRotation + FRotator(0.f, theta, 0.f);
		SetActorRotation(Rotation);
	}
	// アニメーションが終了したら動き出す
	else if (AnimTimer > AnimFinishTime)
	{
		FRotator Rotation = CurrentRotation + FRotator(0.f, TurnAngle, 0.f);
		SetActorRotation(Rotation);

		IsTurn = false;
		TurnAnimFlag = false;
	}
}

void ADog::Eat(float DeltaTime)
{
	if (Fruit == nullptr || EatAnim == nullptr)
	{
		return;
	}

	if (!EatAnimFlag)
	{
		// アニメーションを設定
		DogMesh->PlayAnimation(EatAnim, true);
		WalkAnimFlag = false;
		EatAnimFlag = true;

		// アニメーションを開始
		AnimTimer = 0.f;

		// アニメーション通知時刻を取得
		AnimNotifyTimes(EatAnim);

		// 回転
		CurrentRotation = GetActorRotation();
		FRotator Rotation = CurrentRotation + FRotator(0.f, 0.f, -10.f);
		SetActorRotation(Rotation);

		// 現在の回転角度を取得
		EatRotation = CurrentRotation;
	}

	AnimTimer += DeltaTime;

	// アニメーションの途中でフルーツを咥える
	if (AnimTimer > AnimNotifyTime && !IsFruit)
	{
		// フルーツの重力をオフ
		Fruit->ItemMesh->SetSimulatePhysics(false);

		IsFruit = true;
	}
	// アニメーションが終了したら動き出す
	else if (AnimTimer > AnimFinishTime)
	{
		// 回転を戻す
		SetActorRotation(CurrentRotation);

		IsEat = false;
		EatAnimFlag = false;
	}

	// フルーツを咥えていることを伝える
	Fruit->SetIsEat(IsEat);
}

void ADog::MoveFruit()
{
	if (!DogMesh->DoesSocketExist(SocketName))
	{
		return;
	}

	// プレイヤーがフルーツを獲得したら咥えるのをやめる
	if (Fruit->GetIsGet())
	{
		IsFruit = false;
		return;
	}

	// 犬の口元の位置を取得
	FVector MouseLocation = DogMesh->GetSocketLocation(SocketName);
	FRotator MouseRotation = CurrentRotation - EatRotation;

	// フルーツの位置を口元に設定し、回転も合わせる
    Fruit->ItemMesh->SetWorldLocationAndRotation(MouseLocation, MouseRotation, false, nullptr, ETeleportType::TeleportPhysics);
}

bool ADog::IsArrivePoint(float DeltaTime)
{
	if (MovePoints.Num() < 2)
	{
		return false;
	}

	// 現在地と移動するポイントを取得
	FVector CurrentLocation = GetActorLocation();
	FVector GoalLocation = MovePoints[PointNum];

	// 距離を計算
	float Distance = FVector::Dist(CurrentLocation, GoalLocation);

	// 近づいたらtrueを返す
	if (Distance < (Speed * DeltaTime) / 2.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ADog::IsGoalRight()
{
	// 左方向のベクトルを取得
	FVector LeftVector = GetActorForwardVector();

	// 移動方向を設定
	FVector CurrentLocation = GetActorLocation();
	FVector GoalLocation = MovePoints[PointNum];
	FVector MoveDirection = GoalLocation - CurrentLocation;

	// 内積を計算
	float DotProduct = FVector::DotProduct(LeftVector, MoveDirection);

	if (DotProduct > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ADog::AnimNotifyTimes(UAnimationAsset* Anim)
{
	if (Anim == nullptr)
	{
		return;
	}

	// アニメーション通知時間を取得
	UAnimSequence* AnimSequence = Cast<UAnimSequence>(Anim);
	TArray<FAnimNotifyEvent>& NotifyEvents = AnimSequence->Notifies;
	if (NotifyEvents.Num() >= 2)
	{
		// 通知時間と終了時間を取得
		AnimNotifyTime = NotifyEvents[0].GetTriggerTime();
		AnimFinishTime = NotifyEvents[1].GetTriggerTime();
	}
}
