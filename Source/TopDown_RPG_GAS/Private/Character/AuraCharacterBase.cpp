// Copyright 13


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"


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

void AAuraCharacterBase::InitializePrimaryAttributes()
{
	
	const auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitialPrimaryAttributesEffect, 1.f, AbilitySystemComponent->MakeEffectContext());
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);
}
