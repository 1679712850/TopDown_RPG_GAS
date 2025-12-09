// Copyright 13


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


class UAttributeSet;

AAuraEffectActor::AAuraEffectActor()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectTo(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectTo(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectTo(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectTo(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectTo(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectTo(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		auto ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
		if (!IsValid(ASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemoved;
		for (const auto& ActivateEffectHandle : ActivateEffectHandles)
		{
			if (ActivateEffectHandle.Value == ASC)
			{
				ASC->RemoveActiveGameplayEffect(ActivateEffectHandle.Key, 1);
				HandlesToRemoved.Add(ActivateEffectHandle.Key);
			}
		}

		for (auto& ToRemoved : HandlesToRemoved)
		{
			ActivateEffectHandles.FindAndRemoveChecked(ToRemoved);
		}
	}
}

void AAuraEffectActor::ApplyEffectTo(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (TargetActor == nullptr) return;
	auto ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

	check(GameplayEffectClass);
	auto Context = ASC->MakeEffectContext();
	Context.AddSourceObject(this);
	const auto EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, Context);
	const auto ActivateEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const auto bIsInfinite = EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActivateEffectHandles.Add(ActivateEffectHandle, ASC);
	}
}
