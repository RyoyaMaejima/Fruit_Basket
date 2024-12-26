// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FruitBasket/UI/MyGameInstance.h"
#include "Fruit.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FruitManager.generated.h"

UCLASS()
class FRUITBASKET_API AFruitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFruitManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// フルーツのブループリント
	UPROPERTY(EditAnywhere, Category = "Component")
	TArray<TSubclassOf<AActor>> FruitBluePrints;

	// カットフルーツのブループリント
	UPROPERTY(EditAnywhere, Category = "Component")
	TArray<TSubclassOf<AActor>> FruitBluePrints_Cut;

	// フルーツの初期配置
    UPROPERTY(EditAnywhere, Category = "Component")
    TArray<FVector> FruitLocations;

	// ゴールに置かれるカットフルーツの位置
	UPROPERTY(EditAnywhere, Category = "Component")
    FVector GoalLocation;

	// 集めるべきフルーツの数
	UPROPERTY(EditAnywhere, Category = "Component")
	int32 CollectFruitNum = 5;

	// 集めるべきフルーツの名前とゴールに持っていったかどうかを表す辞書型配列
	TMap<FString, int32> CollectFruits;

	// 集めたフルーツが正しいか判定する
	int32 IsCorrectFruit();

protected:
	// フルーツのカウント数を計算する
	void CalcFruitCount();

	// フルーツのカウント数を増やす
	void AddFruitCount(FString ActorName);

	// フルーツのカウント数を減らす
	void SubFruitCount(FString ActorName);

	// 集めるフルーツを設定する
	void SetCollectFruits();

	// フルーツを配置する
	void PlaceFruits();

private:
	// ゲームインスタンス保存用
	UMyGameInstance* GameInstance = nullptr;

	// 全フルーツの名前と獲得したかどうかを表す辞書型配列
	TMap<FString, int32> FruitMap =
	{
		{TEXT("Apple"), 0},
		{TEXT("Avocado"), 0},
		{TEXT("Banana"), 0},
		{TEXT("Lemon"), 0},
		{TEXT("Mango"), 0},
		{TEXT("Orange"), 0},
		{TEXT("Peach"), 0},
		{TEXT("Pear"), 0},
		{TEXT("Plum"), 0},
		{TEXT("Tomato"), 0},
	};

	// 配置したフルーツのアクター
	TArray<AFruit*> FruitActors;

	// カゴに入ったフルーツのカウント数
	int FruitCount = 0;

	// フルーツの名前を取得
	FString GetFruitName(FString ActorName);

	// 特定のフルーツを削除
	void DeleteFruit(FString FruitName);

	// 特定のカットフルーツをゴールに置く
	void PlaceCutFruitToGoal(FString FruitName);
};
