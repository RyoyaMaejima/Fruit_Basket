// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StageSelectHUD.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AStageSelectHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void DispTutorial(const bool IsTutorial);

private:
	UUserWidget* TutorialWidget;

	UUserWidget* UserWidget;
};
