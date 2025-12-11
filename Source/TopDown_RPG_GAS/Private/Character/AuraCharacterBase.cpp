// Copyright 13


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"



AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level)
{
	check(AbilitySystemComponent)
	check(EffectClass)
	auto Context = AbilitySystemComponent->MakeEffectContext();
	Context.AddSourceObject(this);
	const auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, Level, Context);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);
}

void AAuraCharacterBase::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributesEffect);
	ApplyEffectToSelf(DefaultSecondaryAttributesEffect);
	ApplyEffectToSelf(DefaultVitalAttributesEffect);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	AuraASC->AddCharacterAbilities(StartupAbilities);
}
