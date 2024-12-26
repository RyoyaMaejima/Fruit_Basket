// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "FruitBasket/Stage/FruitManager.h"
#include "MyGameInstance.h"

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

bool UStatusWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	TextBlockTotalFruit->TextDelegate.BindUFunction(this, "SetTextBlockTotalFruit");
	// TextBlockTotalLifes->TextDelegate.BindUFunction(this, "SetTextBlockTotalLifes");
	TextBlockMinutes->TextDelegate.BindUFunction(this, "SetTextBlockMinutes");
	TextBlockSeconds->TextDelegate.BindUFunction(this, "SetTextBlockSeconds");

	AFruitManager* FruitManager = Cast<AFruitManager>(UGameplayStatics::GetActorOfClass(this, AFruitManager::StaticClass()));

	// 画像を設定
	icons.Add(icon_1);
	icons.Add(icon_2);
	icons.Add(icon_3);
	icons.Add(icon_4);
	icons.Add(icon_5);

	if (FruitManager == nullptr){ return false; }

	// for (int i = 0; i < FruitManager->CollectFruitNum; i++)
	// {
	// 	FruitName = FruitManager->CollectFruits[i];
	// 	IconPath = "/Game/UI/icon/icon_" + FruitName;
   	//  	NewIcon = LoadObject<UTexture2D>(nullptr, (*IconPath));
   	// 	SetIcon(icons[i], NewIcon);
	// }

	icons[0]->BrushDelegate.BindUFunction(this, "SetBrush0");
	icons[1]->BrushDelegate.BindUFunction(this, "SetBrush1");
	icons[2]->BrushDelegate.BindUFunction(this, "SetBrush2");
	icons[3]->BrushDelegate.BindUFunction(this, "SetBrush3");
	icons[4]->BrushDelegate.BindUFunction(this, "SetBrush4");

	return true;
}

FText UStatusWidget::SetTextBlockTotalFruit()
{
	// GameInstanceを取得する
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		// GameInstanceのTotalFruitをTextに設定する
		return FText::FromString(FString::FromInt(GameInstance->FruitCount));
	}

	return FText();
}

/*
FText UStatusWidget::SetTextBlockTotalLifes()
{
	// GameInstanceを取得する
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		// GameInstanceのTotalLifesをTextに設定する
		return FText::FromString(FString::FromInt(GameInstance->TotalLifes));
	}

	return FText();
}
*/

FText UStatusWidget::SetTextBlockMinutes()
{
	// GameInstanceを取得する
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		const int32 NumMinutes = GameInstance->TimeLeft / 60;

		// GameInstanceのTimeLeftをTextに設定する
		//return FText::FromString(FString::FromInt(GameInstance->TimeLeft / 60));
		return FText::FromString(FString::Printf(TEXT("%02d"), NumMinutes));
	}

	return FText();
}

FText UStatusWidget::SetTextBlockSeconds()
{
	// GameInstanceを取得する
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		const int32 NumSeconds = GameInstance->TimeLeft % 60;

		// GameInstanceのTimeLeftをTextに設定する
		//return FText::FromString(FString::FromInt(GameInstance->TimeLeft % 60));
		return FText::FromString(FString::Printf(TEXT("%02d"), NumSeconds));
	}

	return FText();
}

void UStatusWidget::SetIcon(UImage* icon, UTexture2D* newIcon)
{
	 if (icon && newIcon)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(newIcon);
        icon->SetBrush(Brush);
		UE_LOG(LogTemp, Display, TEXT("flag"));
    }
}

FSlateBrush UStatusWidget::SetBrush(int32 IconNum)
{
	FSlateBrush Brush;

	if (AFruitManager* FruitManager = Cast<AFruitManager>(UGameplayStatics::GetActorOfClass(this, AFruitManager::StaticClass())))
	{
		int i = 0;
		for (auto& CollectFruit : FruitManager->CollectFruits)
		{
			if (i == IconNum)
			{
				FruitName = CollectFruit.Key;
				if (CollectFruit.Value == 1)
				{
					IconPath = "/Game/UI/icon/icon_gray_" + FruitName;
				}
				else
				{
					IconPath = "/Game/UI/icon/icon_" + FruitName;
				}
				NewIcon = LoadObject<UTexture2D>(nullptr, (*IconPath));
				Brush.SetResourceObject(NewIcon);
				break;
			}
			i++;
		}
	}

	return Brush;
}

FSlateBrush UStatusWidget::SetBrush0()
{
	return SetBrush(0);
}

FSlateBrush UStatusWidget::SetBrush1()
{
	return SetBrush(1);
}

FSlateBrush UStatusWidget::SetBrush2()
{
	return SetBrush(2);
}

FSlateBrush UStatusWidget::SetBrush3()
{
	return SetBrush(3);
}

FSlateBrush UStatusWidget::SetBrush4()
{
	return SetBrush(4);
}