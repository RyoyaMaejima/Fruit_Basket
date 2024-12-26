// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageSelectWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class FRUITBASKET_API UStageSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// NativeConstruct
	void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTitle;

	// ButtonPlayのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonTitleClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonStage1;

	// ButtonQuitのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonStage1Clicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonStage2;

	// ButtonQuitのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonStage2Clicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTutorial;

	// ButtonQuitのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonTutorialClicked();

};
