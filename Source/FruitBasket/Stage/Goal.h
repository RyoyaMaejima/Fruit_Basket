// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FruitBasket/UI/MyGameInstance.h"
#include "FruitManager.h"
#include "CoreMinimal.h"
#include "MyActor.h"
#include "Goal.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AGoal : public AMyActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *PastryMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *BowlMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *GoalLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent *GoalText;

	// 正解音
    UPROPERTY(EditAnywhere, Category = "Component")
    USoundWave* CorrectSE;
	
	// 不正解音
    UPROPERTY(EditAnywhere, Category = "Component")
    USoundWave* InCorrectSE;

	// フルーツを渡す音
    UPROPERTY(EditAnywhere, Category = "Component")
    USoundWave* FruitSE;

private:
	// フルーツマネージャー保存用
	AFruitManager* FruitManager = nullptr;

	// ゲームインスタンス保存用
	UMyGameInstance* GameInstance = nullptr;

	// ゴール可能か
	bool CanGoal = true;

	// ゴールしたか
	bool IsGoal = false;

	// 正解したか
	int32 IsCorrect = false;
};
