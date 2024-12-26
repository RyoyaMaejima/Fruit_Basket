// Fill out your copyright notice in the Description page of Project Settings.

#include "Wood.h"

// Sets default values
AWood::AWood()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AWood::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AActor *PActor = GetAcceptableActor(PlayerTag);
    AActor *OActor = GetAcceptableActor(ObstacleTag);

    // プレイヤーが接触したとき
    if (PActor != nullptr)
    {
        // カゴに入っていなければカゴに入れる
        if (!IsGet)
        {
            Player = PActor;
            IsGet = true;
            ResetBlink(false);
            PlayerGetItem();
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

        // 一定時間経ったら点滅解除して初期位置に戻す
        if (IsBlinkFin)
        {
            ResetBlink(true);
        }
    }

    // 風が吹いているとき
    if (OActor == nullptr && (IsGet || IsBlink))
    {
        WindBlow();
    }
}