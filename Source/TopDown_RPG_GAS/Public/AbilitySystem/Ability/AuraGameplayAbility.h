// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="Ability")
	FGameplayTag StartupAbilityTag;

	UPROPERTY(EditAnywhere,Category="Ability")
	FScalableFloat Damage;	
};
