// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * This macro defines a set of helper functions for accessing and initializing attributes.
 *
 * The following example of the macro:
 *		ATTRIBUTE_ACCESSORS(ULyraHealthSet, Health)
 * will create the following functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag,TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	/*
	 * Primary Attributes Accessors
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	/*
	 * Secondary Attributes Accessors
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);


	/*
	 * Vital Attributes Accessors
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	/*
	 * Meta Attributes Accessors
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);
	
protected:
	/*
	 * Primary Attributes Replication Callbacks
	 */
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldValue);

	/*
	 * Secondary Attributes Replication Callbacks
	 */
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue);
	
	
	/*
	 * Vital Attributes Replication Callbacks
	 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
public:
	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Strength;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Vigor, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Vigor;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Intelligence;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Resilience, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Resilience;

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorPenetration, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData ArmorPenetration;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BlockChance, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData BlockChance;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitChance, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData CriticalHitChance;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitDamage, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData CriticalHitDamage;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitResistance, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData CriticalHitResistance;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthRegeneration, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData HealthRegeneration;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ManaRegeneration, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegeneration;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;
	
	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana, Category="Attributes", Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes",meta=(AllowPrivateAccess = true))
	FGameplayAttributeData IncomingDamage;
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
