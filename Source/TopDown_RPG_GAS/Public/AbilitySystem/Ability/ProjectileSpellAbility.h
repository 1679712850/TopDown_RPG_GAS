// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "DamageGameplayAbility.h"
#include "ProjectileSpellAbility.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UProjectileSpellAbility : public UDamageGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& TargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly)	
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
