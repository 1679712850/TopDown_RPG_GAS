// Copyright 13


#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::OnEffectApplied);
}

void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const auto& Tag : TagContainer)
	{
		// TODO:Broadcast the Tag to the Widget Controller
		GEngine->AddOnScreenDebugMessage(-1,
		                                      5.f,
		                                      FColor::Blue,
		                                      FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString()));
	}
}
