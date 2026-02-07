// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfoDataAsset;
class UAttributeSet;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetPlayerXP() const { return XP; }
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
    FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }
	
	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);
	void AddToAttributePoints(int32 InPoints);
    void AddToSpellPoints(int32 InPoints);
	
	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);
	
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
    FOnPlayerStatChanged OnSpellPointsChangedDelegate;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfoDataAsset> LevelUpInfo;
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
    int32 AttributePoints = 0;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
    int32 SpellPoints = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
	UFUNCTION()
    void OnRep_AttributePoints(int32 OldAttributePoints);

    UFUNCTION()
    void OnRep_SpellPoints(int32 OldSpellPoints);
};
