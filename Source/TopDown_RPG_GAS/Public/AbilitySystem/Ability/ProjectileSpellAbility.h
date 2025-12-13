// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "ProjectileSpellAbility.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UProjectileSpellAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& TargetLocation);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly)	
	TSubclassOf<AAuraProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
