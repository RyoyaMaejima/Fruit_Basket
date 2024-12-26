// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyGameInstance.h"

void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ButtonRetryのOnClickedに「OnButtonRetryClicked」を関連づける
	ButtonRetry->OnClicked.AddUniqueDynamic(this, &UResultWidget::OnButtonRetryClicked);

	// ButtonTitleのOnClickedに「OnButtonTitleClicked」を関連づける
	ButtonTitle->OnClicked.AddUniqueDynamic(this, &UResultWidget::OnButtonTitleClicked);

	// ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UResultWidget::OnButtonQuitClicked);
}

bool UResultWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	//TextBlockTotalFruit->TextDelegate.BindUFunction(this, "SetTextBlockTotalFruit");
	TextBlockMinutes->TextDelegate.BindUFunction(this, "SetTextBlockMinutes");
	TextBlockSeconds->TextDelegate.BindUFunction(this, "SetTextBlockSeconds");

	return true;
}

// FText UResultWidget::SetTextBlockTotalFruit()
// {
// 	// GameInstanceを取得する
// 	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
// 	{
// 		// GameInstanceのTotalFruitをTextに設定する
//         return FText::FromString(FString::Printf(TEXT("%03d"), GameInstance->TotalFruit));
// 	}

// 	return FText();
// }

void UResultWidget::OnButtonRetryClicked()
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

void UResultWidget::OnButtonTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}

void UResultWidget::OnButtonQuitClicked()
{
	// PlayerControllerを取得する
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		// ゲームを終了する
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}

FText UResultWidget::SetTextBlockMinutes()
{
	// GameInstanceを取得する
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		const int32 NumMinutes = (GameInstance->LimitTime - GameInstance->TimeLeft) / 60;

		// GameInstanceのTimeLeftをTextに設定する
		//return FText::FromString(FString::FromInt(GameInstance->TimeLeft / 60));
		return FText::FromString(FString::Printf(TEXT("%02d"), NumMinutes));
	}

	return FText();
}

FText UResultWidget::SetTextBlockSeconds()
{
		// GameInstanceを取得する
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		const int32 NumSeconds = (GameInstance->LimitTime - GameInstance->TimeLeft) % 60;

		// GameInstanceのTimeLeftをTextに設定する
		//return FText::FromString(FString::FromInt(GameInstance->TimeLeft % 60));
		return FText::FromString(FString::Printf(TEXT("%02d"), NumSeconds));
	}

	return FText();
}