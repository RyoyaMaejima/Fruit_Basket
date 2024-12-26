// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectWidget.h"
#include "StageSelectHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyGameInstance.h"

void UStageSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ButtonPlayのOnClickedに「OnButtonPlayClicked」を関連づける
	ButtonTitle->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonTitleClicked);

    // ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonStage1->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage1Clicked);

    // ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonStage2->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage2Clicked);

	// ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonTutorial->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonTutorialClicked);
}

void UStageSelectWidget::OnButtonTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}

void UStageSelectWidget::OnButtonStage1Clicked()
{
	// GameInstanceの変数を初期化する
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->Initialize();

	// Level01をLoadする
	// UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("test")));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage1")));
}

void UStageSelectWidget::OnButtonStage2Clicked()
{
	// GameInstanceの変数を初期化する
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->Initialize();

	// Level01をLoadする
	// UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("test")));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage2")));
}

void UStageSelectWidget::OnButtonTutorialClicked()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    AStageSelectHUD* HUD = Cast<AStageSelectHUD>(PlayerController->GetHUD());

	// if(PlayerController) UE_LOG(LogTemp, Display, TEXT("test1"));
	// if(HUD) UE_LOG(LogTemp, Display, TEXT("test2"));

    HUD->DispTutorial(true);
}