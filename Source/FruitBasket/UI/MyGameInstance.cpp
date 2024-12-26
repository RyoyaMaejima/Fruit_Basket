// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Initialize()
{
	// 初期値を持つ同じクラスのDefaultObjectを取得する
	const UMyGameInstance* DefaultObject = GetDefault<UMyGameInstance>();

	// 初期値を設定する
	this->FruitCount = DefaultObject->FruitCount;

	// タイマーリセット
	ResetTimer();
	StartTimer();
}

void UMyGameInstance::SetFruitCount(int32 newFruitCount)
{
	FruitCount = newFruitCount;
}

void UMyGameInstance::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &UMyGameInstance::UpdateTimer, 1.0f, true);
    UE_LOG(LogTemp, Display, TEXT("Timer started."));
}

void UMyGameInstance::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(_TimerHandle);
    UE_LOG(LogTemp, Display, TEXT("Timer stopped."));
}

void UMyGameInstance::PauseTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(_TimerHandle);
    UE_LOG(LogTemp, Display, TEXT("Timer paused."));
}

void UMyGameInstance::RestartTimer()
{
	GetWorld()->GetTimerManager().UnPauseTimer(_TimerHandle);
    UE_LOG(LogTemp, Display, TEXT("Timer restarted."));
}

void UMyGameInstance::ResetTimer()
{
	TimeLeft = LimitTime;
}

void UMyGameInstance::UpdateTimer()
{
	if(TimeLeft <= 0){
		UE_LOG(LogTemp, Warning, TEXT("Time's UP!"));
		StopTimer();
		//ResetTimer();
		//StartTimer();
		UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("GameOver")));
	} else {
		TimeLeft -= 1;
		UE_LOG(LogTemp, Display, TEXT("Time Remaining: %d"), TimeLeft);
	}
}

void UMyGameInstance::GoResult()
{
	// StopTimer();
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Result")));
}