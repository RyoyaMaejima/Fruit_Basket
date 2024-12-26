// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "StageSelectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ButtonResumeのOnClickedに「OnButtonResumeClicked」を関連づける
	ButtonClose->OnClicked.AddUniqueDynamic(this, &UTutorialWidget::OnButtonCloseClicked);
}

void UTutorialWidget::OnButtonCloseClicked()
{
    const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    AStageSelectHUD* HUD = Cast<AStageSelectHUD>(PlayerController->GetHUD());

    HUD->DispTutorial(false);
}