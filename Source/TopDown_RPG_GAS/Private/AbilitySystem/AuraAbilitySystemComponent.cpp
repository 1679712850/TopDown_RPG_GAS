// Copyright 13


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/Ability/AuraGameplayAbility.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::OnEffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const auto& StartupAbility : StartupAbilities)
	{
		auto Spec = FGameplayAbilitySpec(StartupAbility);
		if (auto AuraAbility = Cast<UAuraGameplayAbility>(Spec.Ability))
		{
			Spec.GetDynamicSpecSourceTags().AddTag(AuraAbility->StartupAbilityTag);
			GiveAbility(Spec);
		}
	}
}

void UAuraAbilitySystemComponent::OnAbilityTagInputHeld(FGameplayTag InputTag)
{
	for (auto& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Spec);
			if (Spec.IsActive())
			{
				TryActivateAbility(Spec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::OnAbilityTagInputReleased(FGameplayTag InputTag)
{
	for (auto& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Spec);
		}
	}
}

void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
