// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockTotalFruit;

	// UPROPERTY(meta = (BindWidget))
	// class UTextBlock* TextBlockTotalLifes;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockMinutes;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlockSeconds;

    UPROPERTY(meta = (BindWidget))
    class UImage* icon_1;

	UPROPERTY(meta = (BindWidget))
    class UImage* icon_2;

	UPROPERTY(meta = (BindWidget))
    class UImage* icon_3;

	UPROPERTY(meta = (BindWidget))
    class UImage* icon_4;

	UPROPERTY(meta = (BindWidget))
    class UImage* icon_5;

	TArray<UImage*> icons;

protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

private:
	UFUNCTION()
	FText SetTextBlockTotalFruit();

	// UFUNCTION()
	// FText SetTextBlockTotalLifes();

	UFUNCTION()
	FText SetTextBlockMinutes();

	UFUNCTION()
	FText SetTextBlockSeconds();

	UFUNCTION()
    void SetIcon(UImage* icon, UTexture2D* newIcon);

	UFUNCTION()
    FSlateBrush SetBrush(int32 IconNum);

	UFUNCTION()
    FSlateBrush SetBrush0();

	UFUNCTION()
    FSlateBrush SetBrush1();

	UFUNCTION()
    FSlateBrush SetBrush2();

	UFUNCTION()
    FSlateBrush SetBrush3();

	UFUNCTION()
    FSlateBrush SetBrush4();

	// アイコン画像更新用バッファ
	UTexture2D* NewIcon;

	FString FruitName;

	FString IconPath;
};
