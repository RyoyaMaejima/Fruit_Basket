// Fill out your copyright notice in the Description page of Project Settings.

#include "Tree.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATree::ATree()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // mesh
    TreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree Mesh"));
    RootComponent = TreeMesh;
}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	
    // ウィンドを取得
    Wind = Cast<AWind>(UGameplayStatics::GetActorOfClass(this, AWind::StaticClass()));
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (Wind == nullptr)
    {
        return;
    }

    // 風が吹いたとき
    if (!IsWind && Wind->GetIsWind())
    {
        IsWind = Wind->GetIsWind();
        PlaceLeafs();
    }

    // 風が止まったとき
    if (IsWind && !Wind->GetIsWind())
    {
        IsWind = Wind->GetIsWind();
        DeleteAllLeafs();
    }
}

void ATree::PlaceLeafs()
{
    if (LeafBluePrint == nullptr)
    {
        return;
    }

    for (int i = 0; i < LeafNum; i++)
    {
        // アクターの座標を取得
        FVector ActorLocation = GetActorLocation();

        // 座標をランダムに決定
        float LocX = ActorLocation.X + FMath::RandRange(LeafMinRange.X, LeafMaxRange.X);
        float LocY = ActorLocation.Y + FMath::RandRange(LeafMinRange.Y, LeafMaxRange.Y);
        float LocZ = ActorLocation.Z + FMath::RandRange(LeafMinRange.Z, LeafMaxRange.Z);
        FVector LeafLocation = FVector(LocX, LocY, LocZ);

        // 回転をランダムに決定
        float RatX = FMath::RandRange(0.f, 90.f);
        float RatY = FMath::RandRange(0.f, 90.f);
        float RatZ = FMath::RandRange(0.f, 90.f);
        FRotator LeafRotation = FRotator(RatX, RatY, RatZ);

        // 葉っぱを配置
        ALeaf* LeafActor = GetWorld()->SpawnActor<ALeaf>(LeafBluePrint, LeafLocation, LeafRotation);

        // リストに追加
        LeafActors.Add(LeafActor);
    }
}

void ATree::DeleteAllLeafs()
{
    if (LeafActors.Num() < 1)
    {
        return;
    }

    // 葉っぱをすべて削除
    for (ALeaf* LeafActor : LeafActors)
    {
        LeafActor->Destroy();
    }

    // リストを空にする
    LeafActors.Empty();
}