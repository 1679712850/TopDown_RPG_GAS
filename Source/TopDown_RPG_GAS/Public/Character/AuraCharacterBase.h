// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;

UCLASS(Abstract)
class TOPDOWN_RPG_GAS_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface , public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly ,EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesEffect;

	UPROPERTY(BlueprintReadOnly ,EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesEffect;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level = 1.f);

	void InitializeDefaultAttributes();
	
};
