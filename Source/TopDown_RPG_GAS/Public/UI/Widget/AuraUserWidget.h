// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetWidgetController(UObject* InController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
