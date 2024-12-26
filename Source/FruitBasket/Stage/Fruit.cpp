// Fill out your copyright notice in the Description page of Project Settings.

#include "Fruit.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFruit::AFruit()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AFruit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFruit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AActor *PActor = GetAcceptableActor(PlayerTag);
    AActor *OActor = GetAcceptableActor(ObstacleTag);

    // プレイヤーが接触したとき
    if (PActor != nullptr)
    {
        // 犬が咥えている途中だと獲得できない
        if (!IsEat)
        {
            // カゴに入っていなければカゴに入れる
            if (!IsGet)
            {
                Player = PActor;
                IsGet = true;
                ResetBlink(false);
                PlayerGetItem();
                AddFruitCount();
            }
        }
    }
    // カゴから出たとき
    else if (IsOut())
    {
        if (IsGet)
        {
            IsGet = false;
            IsBlink = true;
        }
    }

    // 点滅中
    if (IsBlink)
    {
        Blink(DeltaTime);

        // 犬が咥えたら点滅解除
        if (IsEat)
        {
            ResetBlink(true);
            SubFruitCount();
        }
        // 一定時間経ったら点滅解除して初期位置に戻す
        else if (IsBlinkFin)
        {
            ResetBlink(true);
            SubFruitCount();
        }
    }

    // 風が吹いているとき
    if (OActor == nullptr && (IsGet || IsBlink))
    {
        WindBlow();
    }
}

bool AFruit::GetIsAdd() const
{
    return IsAdd;
}

void AFruit::SetIsAdd(bool NewIsAdd)
{
    IsAdd = NewIsAdd;
}

bool AFruit::GetIsSub() const
{
    return IsSub;
}

void AFruit::SetIsSub(bool NewIsSub)
{
    IsSub = NewIsSub;
}

void AFruit::AddFruitCount()
{
    if (IsCount)
    {
        return;
    }
    
    // 加算イベントフラグを立てる
    IsAdd = true;
    IsCount = true;
}

void AFruit::SubFruitCount()
{
    if (!IsCount)
    {
        return;
    }
    
    // 減算イベントフラグを立てる
    IsSub = true;
    IsCount = false;
}