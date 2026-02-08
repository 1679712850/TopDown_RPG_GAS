// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpellAbility.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraFireBolt : public UProjectileSpellAbility
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	float ProjectileSpread = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	int32 MaxNumProjectiles = 5;
};
