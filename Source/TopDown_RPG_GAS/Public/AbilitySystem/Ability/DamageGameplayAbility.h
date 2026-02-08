// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;
};
