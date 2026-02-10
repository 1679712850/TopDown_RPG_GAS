// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraProjectile.h"
#include "AuraFireBall.generated.h"

UCLASS()
class TOPDOWN_RPG_GAS_API AAuraFireBall : public AAuraProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraFireBall();

protected:
	virtual void BeginPlay() override;
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
