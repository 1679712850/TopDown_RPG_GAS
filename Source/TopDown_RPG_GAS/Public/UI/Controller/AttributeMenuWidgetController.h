// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "AttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, AttributeInfo);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class TOPDOWN_RPG_GAS_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="Aura|Attributes")
	FOnPlayerStatChangedSignature AttributePointsChangedDelegate;
	
	UFUNCTION(BlueprintCallable)
	void UpgradeAttribute(const FGameplayTag& AttributeTag);
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="AttributeMenuWidgetController")
	TObjectPtr<class UAttributeInfoDataAsset> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute);

};
