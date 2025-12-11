// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
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
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="AttributeMenuWidgetController")
	TObjectPtr<class UAttributeInfoDataAsset> AttributeInfo;
};
