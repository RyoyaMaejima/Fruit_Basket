// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Fruit.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AFruit : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFruit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsAdd() const;

	void SetIsAdd(bool IsAdd);

	bool GetIsSub() const;

	void SetIsSub(bool IsSub);

protected:
	// フルーツのカウント数を増やす
    void AddFruitCount();

    // フルーツのカウント数を減らす
    void SubFruitCount();

private:
	// 加算や減算が連続して起こらないようにするためのフラグ
	bool IsCount = false;
	
	// 加算イベントフラグ
    bool IsAdd = false;

	// 減算イベントフラグ
	bool IsSub = false;
};
