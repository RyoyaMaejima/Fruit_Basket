// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundWave.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class FRUITBASKET_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent *Trigger;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UAudioComponent *Audio;

	// プレイヤータグ
	UPROPERTY(EditAnywhere, Category = "Component")
    FName PlayerTag = "Player";

	// フルーツタグ
	UPROPERTY(EditAnywhere, Category = "Component")
    FName FruitTag = "Fruit";

	// ウッドタグ
	UPROPERTY(EditAnywhere, Category = "Component")
    FName WoodTag = "Wood";

	// 障害物タグ
	UPROPERTY(EditAnywhere, Category = "Component")
	FName ObstacleTag = "Obstacle";

protected:
	// オーバーラップしたアクターの中でタグが正しければそのアクターを返す
    AActor* GetAcceptableActor(FName AcceptableActorTag) const;

	// オーバーラップしたアクターの中でタグが正しければそのアクターをリストに渡す
    void GetAcceptableActors(FName AcceptableActorTag, TArray<AActor*>* OverlapActors);

    // SEを鳴らす
    void PlaySE(USoundWave* SE);
};
