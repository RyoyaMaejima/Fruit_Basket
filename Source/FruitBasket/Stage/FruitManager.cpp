// Fill out your copyright notice in the Description page of Project Settings.

#include "FruitManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFruitManager::AFruitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 集めるフルーツを設定
	SetCollectFruits();
}

// Called when the game starts or when spawned
void AFruitManager::BeginPlay()
{
	Super::BeginPlay();
	
	// ゲームインスタンスを取得
    GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// フルーツを配置
	PlaceFruits();
}

// Called every frame
void AFruitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalcFruitCount();
}

int32 AFruitManager::IsCorrectFruit()
{
	if (GameInstance == nullptr || CollectFruits.Num() < 1)
	{
		return -1;
	}

	// 全て正しいか
	bool isAllCorect = true;
	// 全て間違っているか
	bool isAllIncorect = true;

	for (auto& CollectFruit : CollectFruits)
	{
		if (CollectFruit.Value != 1)
		{
			// フルーツが正しいとき
			if (FruitMap[CollectFruit.Key] > 0)
			{
				CollectFruit.Value = 1;
				DeleteFruit(CollectFruit.Key);
				PlaceCutFruitToGoal(CollectFruit.Key);
				FruitMap[CollectFruit.Key] -= 1;
				FruitCount -= 1;
				GameInstance->SetFruitCount(FruitCount);
				isAllIncorect = false;
			}
			// フルーツが正しくないとき
			else
			{
				isAllCorect = false;
			}
		}
	}

	// 全て正しいとき
	if (isAllCorect)
	{
		return 2;
	}
	// 全て間違っているとき
	else if (isAllIncorect)
	{
		return 0;
	}
	// どちらでもないとき
	else
	{
		return 1;
	}
}

void AFruitManager::CalcFruitCount()
{
	if (FruitActors.Num() < 1)
	{
		return;
	}

	// それぞれのフルーツが獲得されたか
	for (AFruit* FruitActor : FruitActors)
	{
		// 加算イベントフラグが立っているとき
		if (FruitActor->GetIsAdd())
		{
			AddFruitCount(FruitActor->GetName());
			FruitActor->SetIsAdd(false);
		}

		// 減算イベントフラグが立っているとき
		if (FruitActor->GetIsSub())
		{
			SubFruitCount(FruitActor->GetName());
			FruitActor->SetIsSub(false);
		}
	}
}

void AFruitManager::AddFruitCount(FString ActorName)
{
	if (GameInstance == nullptr)
	{
		return;
	}

	FString FruitName = GetFruitName(ActorName);

	// 得点を増やす
	if(FruitMap.Contains(FruitName))
	{
		FruitMap[FruitName] += 1;
		FruitCount += 1;
		GameInstance->SetFruitCount(FruitCount);
	}
}

void AFruitManager::SubFruitCount(FString ActorName)
{
	if (GameInstance == nullptr)
	{
		return;
	}

	FString FruitName = GetFruitName(ActorName);

	// 得点を減らす
	if(FruitMap.Contains(FruitName))
	{
		FruitMap[FruitName] -= 1;
		FruitCount -= 1;
		GameInstance->SetFruitCount(FruitCount);
	}
}

void AFruitManager::SetCollectFruits()
{
	// キーのリストを取得
    TArray<FString> Keys;
    FruitMap.GetKeys(Keys);

    // キーをランダムに選択
    for (int i = 0; i < CollectFruitNum; i++)
    {
        int RandomIndex = FMath::RandRange(0, Keys.Num() - 1);
        FString SelectedKey = Keys[RandomIndex];

        // 選択されたキーをCollectFruitsに追加
        CollectFruits.Add(SelectedKey, 0);

        // 使用済みのキーをリストから削除
        Keys.RemoveAt(RandomIndex);
    }
}

void AFruitManager::PlaceFruits()
{
	if (FruitBluePrints.Num() < 1 || FruitBluePrints.Num() > FruitLocations.Num())
	{
		return;
	}

	// ランダムインデックスのリストを生成
	TArray<int> Indices;
    for (int i = 0; i < FruitLocations.Num(); i++)
    {
        Indices.Add(i);
    }

	// 配置する場所をランダムに選択
	for (int i = 0; i < FruitBluePrints.Num(); i++)
	{
		int RandomIndex = FMath::RandRange(0, Indices.Num() - 1);

		// フルーツを配置
		AFruit* FruitActor = GetWorld()->SpawnActor<AFruit>(FruitBluePrints[i], FruitLocations[Indices[RandomIndex]], FRotator::ZeroRotator);

		// リストに追加
		FruitActors.Add(FruitActor);

		// 使用済みのインデックスをリストから削除
        Indices.RemoveAt(RandomIndex);
	}
}

FString AFruitManager::GetFruitName(FString ActorName)
{
    FString FruitName = ActorName.RightChop(3);

    // アンダースコアの位置を取得
    int UnderscoreIndex = FruitName.Find(TEXT("_"));

    // アンダースコアが見つかった場合
    if (UnderscoreIndex != INDEX_NONE)
    {
        // アンダースコアまでの部分を取得
        FruitName = FruitName.Left(UnderscoreIndex);
    }
	else
	{
		FruitName = FruitName.LeftChop(1);
	}

    // アンダースコアが見つからなかった場合は、元の文字列を返す
    return FruitName;
}

void AFruitManager::DeleteFruit(FString FruitName)
{
	if (FruitActors.Num() < 1)
	{
		return;
	}

	// アクターの名前を検索して削除
	for (AFruit* FruitActor : FruitActors)
    {
		FString ActorName = FruitActor->GetName();
		if (GetFruitName(ActorName) == FruitName)
		{
			FruitActor->Destroy();
			FruitActors.Remove(FruitActor);
			return;
		}
    }
}

void AFruitManager::PlaceCutFruitToGoal(FString FruitName)
{
	if (FruitBluePrints_Cut.Num() < 1)
	{
		return;
	}

	// ブループリントの名前を検索してゴールに配置
	for (TSubclassOf<AActor>& CutFruit : FruitBluePrints_Cut)
    {
		FString ActorName = CutFruit->GetName();
		if (GetFruitName(ActorName) == FruitName)
		{
			GetWorld()->SpawnActor<AActor>(CutFruit, GoalLocation, FRotator::ZeroRotator);
			return;
		}
    }
}