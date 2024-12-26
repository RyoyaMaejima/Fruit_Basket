// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// カゴに入っているフルーツのカウント数
	int32 FruitCount = 0;

public:
	void SetFruitCount(int32 FruitCount);

public:
	// 初期化する
	void Initialize();

public:
	// 制限時間（秒）
	int32 LimitTime = 180;

	// 残り時間（秒）
	int32 TimeLeft;

	// タイマー開始
	void StartTimer();

	// タイマー停止
	void StopTimer();

	// 一時停止
	void PauseTimer();

	// 再開
	void RestartTimer();

	// タイマーリセット
	void ResetTimer();

private:
	// タイマー更新
	void UpdateTimer();

	// タイマーハンドル（タイマー本体）
	FTimerHandle _TimerHandle;

public:
	void GoResult();

};
