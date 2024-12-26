// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundWave.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound.generated.h"

UCLASS()
class FRUITBASKET_API ASound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    class UAudioComponent *Audio;

private:
	// BGM
    UPROPERTY(EditAnywhere, Category = "Component")
    USoundWave* BGM;

	void PlayBGM();
};
