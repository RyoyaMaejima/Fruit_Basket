// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class FRUITBASKET_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// NativeConstruct
	void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonRetry;

	// ButtonRetryのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonRetryClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTitle;

	// ButtonTitleのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonTitleClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuit;

	// ButtonQuitのOnClickedイベントに関連づける
	UFUNCTION()
	void OnButtonQuitClicked();
};
