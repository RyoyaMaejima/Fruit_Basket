// Fill out your copyright notice in the Description page of Project Settings.

#include "Wind.h"
#include "Components/AudioComponent.h"

// Sets default values
AWind::AWind()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWind::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // 風を吹かせる
    if (!IsWind && WindTimer > WindInterval)
    {
        IsWind = true;
        PlaySE(WindSE);
    }

    // 風を止める
    if(IsWind && !Audio->IsPlaying())
    {
        WindTimer = 0.f;
        IsWind = false;
    }

    WindTimer += DeltaTime;
}

FVector AWind::GetWindVector() const
{
    return WindVector;
}

float AWind::GetWindZErea() const
{
    return WindZErea;
}

bool AWind::GetIsWind() const
{
    return IsWind;
}
