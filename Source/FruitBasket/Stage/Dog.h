// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Fruit.h"
#include "CoreMinimal.h"
#include "MyActor.h"
#include "Dog.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API ADog : public AMyActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent *DogMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *BodyCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *FaceCollider;

	// ソケットネーム
	UPROPERTY(EditAnywhere, Category = "Component")
    FName SocketName = "Bip01-Mouse";

	// 移動するポイント
	UPROPERTY(EditAnywhere, Category = "Movement")
    TArray<FVector> MovePoints;

	// スピード
	UPROPERTY(EditAnywhere, Category = "Movement")
    float Speed = 100.f;

	// 歩くアニメーション
	UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimationAsset* WalkAnim;

	// 右に方向転換するアニメーション
	UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimationAsset* TurnRightAnim;

	// 左に方向転換するアニメーション
	UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimationAsset* TurnLeftAnim;

	// 咥えるアニメーション
	UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimationAsset* EatAnim;

protected:
	// フルーツの情報を保存する
    AFruit *Fruit;

	// ターン中か
	bool IsTurn = false;

	// フルーツを咥えている途中か
	bool IsEat = false;

	// フルーツを咥えているか
	bool IsFruit = false;

	// 移動
	void Walk(float DeltaTime);

	// 方向転換
	void Turn(float DeltaTime);

	// 咥える
	void Eat(float DeltaTime);

	// ポイントに到着したか
	bool IsArrivePoint(float DeltaTime);

	// アニメーションに合わせてフルーツを動かす
	void MoveFruit();

private:
	// 現在の回転角度
	FRotator CurrentRotation = FRotator::ZeroRotator;

	// 咥えた瞬間の回転角度
	FRotator EatRotation = FRotator::ZeroRotator;

	// 今何番目のポイントに向かっているか
	int PointNum = 0;

	// 回転角度
	float TurnAngle = 0.f;

	// アニメーションの経過時間
	float AnimTimer = 0.f;

	// アニメーション通知時間
	float AnimNotifyTime = 0.f;

	// アニメーション終了時間
	float AnimFinishTime = 0.f;

	// アニメーションフラグ
	bool WalkAnimFlag = false;

	bool TurnAnimFlag = false;

	bool EatAnimFlag = false;

	// 目的地が右にあるか左にあるか
	bool IsGoalRight();

	// アニメーションの通知時間を取得する
	void AnimNotifyTimes(UAnimationAsset* Anim);
};
