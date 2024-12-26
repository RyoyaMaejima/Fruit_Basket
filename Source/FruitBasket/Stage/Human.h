// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "Human.generated.h"

/**
 * 
 */
UCLASS()
class FRUITBASKET_API AHuman : public AMyActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHuman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent *HumanMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *BodyCollider;

	// アニメーション
	UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimationAsset* Anim;
};
