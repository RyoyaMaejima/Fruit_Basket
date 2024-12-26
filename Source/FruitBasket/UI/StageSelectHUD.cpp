// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AStageSelectHUD::BeginPlay()
{
	// WidgetBlueprintのClassを取得する
	FString Path = TEXT("/Game/BluePrints/BPW_StageSelect.BPW_StageSelect_C");
	TSubclassOf<UUserWidget> WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

	FString TutorialPath = TEXT("/Game/BluePrints/BPW_Tutorial.BPW_Tutorial_C");
	TSubclassOf<UUserWidget> TutorialWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*TutorialPath)).LoadSynchronous();

	// PlayerControllerを取得する
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// WidgetClassとPlayerControllerが取得できたか判定する
	if (WidgetClass && TutorialWidgetClass && PlayerController)
	{
		// Widgetを作成する
		UserWidget = UWidgetBlueprintLibrary::Create(GetWorld(), WidgetClass, PlayerController);

		// Viewportに追加する
		UserWidget->AddToViewport(0);

		// Widgetを作成する
		TutorialWidget = UWidgetBlueprintLibrary::Create(GetWorld(), TutorialWidgetClass, PlayerController);

		TutorialWidget->SetVisibility(ESlateVisibility::Collapsed);

		// Viewportに追加する
		TutorialWidget->AddToViewport(1);

		// MouseCursorを表示する
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, UserWidget, EMouseLockMode::DoNotLock, true, false);
		PlayerController->SetShowMouseCursor(true);
	}
}


void AStageSelectHUD::DispTutorial(const bool IsTutorial)
{
	if (IsTutorial)
	{
		// Pauseメニューを表示する
		TutorialWidget->SetVisibility(ESlateVisibility::Visible);
		UserWidget->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Display, TEXT("test3"));
	}
	else
	{
		// Pauseメニューを折りたたみ状態にする
		TutorialWidget->SetVisibility(ESlateVisibility::Collapsed);
		UserWidget->SetVisibility(ESlateVisibility::Visible);
	}
}