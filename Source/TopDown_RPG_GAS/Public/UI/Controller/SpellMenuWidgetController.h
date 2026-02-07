// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "OverlayWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

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
};
