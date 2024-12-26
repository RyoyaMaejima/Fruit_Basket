// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wind.h"
#include "Leaf.h"
#include "CoreMinimal.h"
#include "MyActor.h"
#include "Tree.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API ATree : public AMyActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *TreeMesh;

	// 葉っぱのブループリント
	UPROPERTY(EditAnywhere, Category = "Component")
	TSubclassOf<AActor> LeafBluePrint;

	// 葉っぱの数
	UPROPERTY(EditAnywhere, Category = "Component")
	int32 LeafNum = 5;

	// 葉っぱの配置範囲（下限）
    UPROPERTY(EditAnywhere, Category = "Component")
    FVector LeafMinRange;

	// 葉っぱの配置範囲（上限）
    UPROPERTY(EditAnywhere, Category = "Component")
    FVector LeafMaxRange;

protected:
	// 風が吹いたか
	bool IsWind = false;

	// 葉っぱを配置する
	void PlaceLeafs();

	// 葉っぱをすべて削除する
	void DeleteAllLeafs();

private:
	// ウィンド保存用
    AWind* Wind = nullptr;

	// 配置した葉っぱのアクター
	TArray<ALeaf*> LeafActors;
};
