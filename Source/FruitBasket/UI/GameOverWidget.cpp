// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyGameInstance.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ButtonRetryのOnClickedに「OnButtonRetryClicked」を関連づける
	ButtonRetry->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::OnButtonRetryClicked);

	// ButtonTitleのOnClickedに「OnButtonTitleClicked」を関連づける
	ButtonTitle->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::OnButtonTitleClicked);

	// ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::OnButtonQuitClicked);
}

void UGameOverWidget::OnButtonRetryClicked()
{
	// GameInstanceの変数を初期化する
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->Initialize();

    // 現在のLevelNameを取得する
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	// StageSelectをLoadする
	// UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("test")));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("StageSelect")));
}

void UGameOverWidget::OnButtonTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}

void UGameOverWidget::OnButtonQuitClicked()
{
	// PlayerControllerを取得する
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		// ゲームを終了する
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}