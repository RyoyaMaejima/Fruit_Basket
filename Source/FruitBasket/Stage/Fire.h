// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "Fire.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AFire : public AMyActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *FireMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UParticleSystemComponent *FireEmitter;

	// 燃える音
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundWave* BurnSE;

protected:
	// 範囲内にある木を燃やす
	void BurnWoods(TArray<AActor *> OverlapActors);
};
