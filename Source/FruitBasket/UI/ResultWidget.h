// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class FRUITBASKET_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// UPROPERTY(meta = (BindWidget))
	// class UTextBlock* TextBlockTotalFruit;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockMinutes;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockSeconds;

protected:
	// NativeConstruct
	void NativeConstruct() override;
	
	bool Initialize() override;

private:
	// UFUNCTION()
	// FText SetTextBlockTotalFruit();

	UFUNCTION()
	FText SetTextBlockMinutes();

	UFUNCTION()
	FText SetTextBlockSeconds();

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
