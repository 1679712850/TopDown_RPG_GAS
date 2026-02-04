// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class UAuraAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer& /* AssetTags */)
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven,UAuraAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility,const FGameplayAbilitySpec& Spec);
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);

	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven OnAbilitiesGivenDelegate;
	
	bool bStartupAbilitiesGiven = false;


	void OnAbilityTagInputHeld(FGameplayTag InputTag);
	void OnAbilityTagInputReleased(FGameplayTag InputTag);
	void ForEachAbility(const FForEachAbility& Delegate);
	
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	virtual void OnRep_ActivateAbilities() override;
protected:
	UFUNCTION(Client,Reliable)
	void ClientOnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
