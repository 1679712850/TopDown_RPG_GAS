// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "OverlayWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled);
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API USpellMenuWidgetController : public UOverlayWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChanged;
	
	UPROPERTY(BlueprintAssignable)
    FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

    UFUNCTION(BlueprintCallable)
    void SpellGlobeSelected(const FGameplayTag& AbilityTag);
    
private:
    static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);
};
