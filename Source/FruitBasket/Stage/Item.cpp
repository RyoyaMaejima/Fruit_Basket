// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // mesh
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
    RootComponent = ItemMesh;

    // trigger
    Trigger->SetupAttachment(ItemMesh);

    // audio
    Audio->SetupAttachment(ItemMesh);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

    // ウィンドを取得
    Wind = Cast<AWind>(UGameplayStatics::GetActorOfClass(this, AWind::StaticClass()));
	
    // アイテムの初期位置を記録
    DefaultLocation = GetActorLocation();
    DefaultRotation = GetActorRotation();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AItem::GetIsGet() const
{
    return IsGet;
}

void AItem::SetIsEat(bool NewIsEat)
{
    IsEat = NewIsEat;
}

void AItem::PlayerGetItem()
{
    if(Player == nullptr)
    {
        return;
    }

    FVector PlayerLocation = Player->GetActorLocation();

    // フルーツをプレイヤーの上に設定
    PlayerLocation.Z += OverZPosition;
    ItemMesh->SetWorldLocation(PlayerLocation, false, nullptr, ETeleportType::TeleportPhysics);
    
    // アイテムの物理挙動をオン
    ItemMesh->SetSimulatePhysics(true);

    // 獲得音を鳴らす
    PlaySE(GetSE);
}

bool AItem::IsOut()
{
    if(Player == nullptr)
    {
        return false;
    }

    // プレイヤーとアイテムの場所を取得
    FVector PlayerLocation = Player->GetActorLocation();
    FVector ItemLocation = GetActorLocation();

    // 距離を計算
    float Distance = FVector::Dist(PlayerLocation, ItemLocation);

    // 離れていたらtrueを返す
    if (Distance > OutDistance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AItem::Blink(float DeltaTime)
{
    //点滅　ついている時に戻る
    if (OnceBlinkTime > 0.2f)
    {
        ItemMesh->SetVisibility(true);
        OnceBlinkTime = 0.f;
    }
    //点滅　消えているとき
    else if (OnceBlinkTime > 0.1f)
    {
        ItemMesh->SetVisibility(false);
    }
    //点滅　ついているとき
    else
    {
        ItemMesh->SetVisibility(true);
    }

    if (BlinkTime == 0.f)
    {
        // 点滅音を鳴らす
        PlaySE(OutSE);
    }

    //一定時間たったら点滅終わり
    if (BlinkTime > OutTime)
    {
        IsBlinkFin = true;
    }
    else
    {
        BlinkTime += DeltaTime;
        OnceBlinkTime += DeltaTime;
    }
}

void AItem::ResetBlink(bool IsLost)
{
    ItemMesh->SetVisibility(true);
    Audio->Stop();
    IsBlink = false;
    IsBlinkFin = false;
    BlinkTime = 0.f;
    OnceBlinkTime = 0.f;

    // アイテムを失ったときは初期位置に戻す
    if (IsLost)
    {
        Player = nullptr;
        SetActorLocation(DefaultLocation);
        SetActorRotation(DefaultRotation);
        ItemMesh->SetSimulatePhysics(false);
    }
}

void AItem::WindBlow()
{
    if (Wind == nullptr)
    {
        return;
    }

    // 各値の取得
    FVector WVector = Wind->GetWindVector();
    float WZErea = Wind->GetWindZErea();
    bool IsWind = Wind->GetIsWind();

    // アイテムの位置を取得
    FVector ItemLocation = GetActorLocation();

    // アイテムが一定座標以上なら力を加える
    if (IsWind && ItemLocation.Z > WZErea)
    {
        ItemMesh->AddForce(WVector, NAME_None, true);
    }
}
