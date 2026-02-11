// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Data/CharacterClassInfo.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class AAuraAIController;
class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class TOPDOWN_RPG_GAS_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;
	
	/* Enemy Interface */
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/* end Enemy Interface */

	/* Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	/* end Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnFloatAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnFloatAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() override;
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Aura")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
	
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;
};
