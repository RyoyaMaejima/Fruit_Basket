// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "Wind.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AWind : public AMyActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 風の方向ベクトル
	UPROPERTY(EditAnywhere, Category = "Component")
	FVector WindVector = FVector::ZeroVector;

	// 風の侵入範囲（Z座標）
	UPROPERTY(EditAnywhere, Category = "Component")
	float WindZErea = 0.f;

	// 風が吹く時間間隔
	UPROPERTY(EditAnywhere, Category = "Component")
	float WindInterval = 5.f;

	// 風が吹く音
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundWave* WindSE;

	FVector GetWindVector() const;

	float GetWindZErea() const;

	bool GetIsWind() const;

protected:
	// 風が吹いてからの経過時間
	float WindTimer = 0.f;

	// 風が吹くイベントのフラグ
	bool IsWind = false;
};
