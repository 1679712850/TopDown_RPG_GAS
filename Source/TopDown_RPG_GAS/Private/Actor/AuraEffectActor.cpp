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
}

void AAuraEffectActor::ApplyEffectTo(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (TargetActor == nullptr) return;
	auto ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

	check(GameplayEffectClass);
	auto Context = ASC->MakeEffectContext();
	Context.AddSourceObject(this);
	auto EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, Context);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
