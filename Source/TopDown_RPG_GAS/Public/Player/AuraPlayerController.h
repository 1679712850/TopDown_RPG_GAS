// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UAuraInputConfig;
class IEnemyInterface;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void OnMove(const FInputActionValue& InputActionValue);

	void CursorTrace();
	IEnemyInterface* LastEnemy;
	IEnemyInterface* CurrentEnemy;

	void AbilityTagInputPressed(FGameplayTag InputTag);
	void AbilityTagInputReleased(FGameplayTag InputTag);
	void AbilityTagInputHeld(FGameplayTag InputTag);

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
};
