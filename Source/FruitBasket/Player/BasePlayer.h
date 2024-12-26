// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePlayer.generated.h"

UCLASS()
class FRUITBASKET_API ABasePlayer : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABasePlayer();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // カプセルコンポーネント
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent *CapsuleComp;
    // ベースメッシュ -- meshを設定
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *BaseMesh;
};
