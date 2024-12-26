// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wind.h"
#include "CoreMinimal.h"
#include "MyActor.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AItem : public AMyActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *ItemMesh;

	// アイテムがカゴのどれだけ上に置かれるか
    UPROPERTY(EditAnywhere, Category = "Component")
    float OverZPosition = -10.f;
    
    // アイテムがカゴからどれだけ離れるとカゴの外と判定されるか
    UPROPERTY(EditAnywhere, Category = "Component")
    float OutDistance = 30.f;

    // アイテムがカゴから何秒離れると初期位置に戻るか
    UPROPERTY(EditAnywhere, Category = "Component")
    float OutTime = 2.f;

    // 獲得音
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundWave* GetSE;

    // 点滅音
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundWave* OutSE;

	bool GetIsGet() const;

    void SetIsEat(bool IsEat);

protected:
	// プレイヤーの情報を保存する
    AActor *Player;

	// アイテムが獲得されたか
    bool IsGet = false;

	// 犬が咥えている途中か
    bool IsEat = false;

	// 点滅中か
    bool IsBlink = false;

	// 点滅終了したか
	bool IsBlinkFin = false;

	// プレイヤーがアイテムを入手したときの挙動
    void PlayerGetItem();

	// フルーツがカゴから離れたか
    bool IsOut();

	// 点滅
    void Blink(float DeltaTime);

    // 点滅の初期化
    void ResetBlink(bool IsLost);

    // 風による移動
    void WindBlow();

private:
    // ウィンド保存用
    AWind* Wind = nullptr;

	// デフォルトの位置
    FVector DefaultLocation = FVector::ZeroVector;

    // デフォルトの回転
    FRotator DefaultRotation = FRotator::ZeroRotator;

	// 点滅時間
    float BlinkTime = 0.f;

    // １回の点滅時間
    float OnceBlinkTime = 0.f;
};
