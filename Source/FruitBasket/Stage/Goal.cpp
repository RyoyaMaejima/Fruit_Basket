// Fill out your copyright notice in the Description page of Project Settings.

#include "Goal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoal::AGoal()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // mesh
    PastryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pastry Mesh"));
    RootComponent = PastryMesh;

	BowlMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Goal Mesh"));
	BowlMesh->SetupAttachment(PastryMesh);

    // trigger
    Trigger->SetupAttachment(PastryMesh);

    // audio
    Audio->SetupAttachment(PastryMesh);

    // light
	GoalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Goal Light"));
	GoalLight->SetupAttachment(PastryMesh);

	// text
	GoalText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Goal Text"));
	GoalText->SetupAttachment(PastryMesh);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
    // ゲームインスタンスを取得
    GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// フルーツマネージャーを取得
    FruitManager = Cast<AFruitManager>(UGameplayStatics::GetActorOfClass(this, AFruitManager::StaticClass()));
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AActor *Actor = GetAcceptableActor(PlayerTag);

	if (Actor != nullptr)
	{
		if (CanGoal)
		{
			// 集めたフルーツを判定
			if (FruitManager != nullptr)
			{
				IsCorrect = FruitManager->IsCorrectFruit();
			}

			// 正しいものが揃ったとき
			if (IsCorrect == 2)
			{
				// 正解音を鳴らす
				PlaySE(CorrectSE);

				// タイマーを止める
				if (GameInstance != nullptr)
				{
					GameInstance->StopTimer();
				}
			}
			// 正しいものが一つでもあるとき
			else if (IsCorrect == 1)
			{
				// フルーツを渡す音を鳴らす
				PlaySE(FruitSE);
			}
			// 全て間違っているとき
			else
			{
				// 不正解音を鳴らす
				PlaySE(InCorrectSE);
			}
			CanGoal = false;
			IsGoal = true;
		}
	}
	else
	{
		CanGoal = true;
	}

	// 音が鳴り終わったら
	if (IsGoal && !Audio->IsPlaying())
	{
		// 正解のとき
		if (IsCorrect == 2)
		{
			// リザルト画面に移行
			if (GameInstance != nullptr)
			{
				GameInstance->GoResult();
			}
		}
		IsGoal = false;
	}
}
