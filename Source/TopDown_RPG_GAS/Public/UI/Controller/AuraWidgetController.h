// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams() = default;
	
	FWidgetControllerParams(const TObjectPtr<APlayerController>& PC,
	                        const TObjectPtr<APlayerState>& PS, const TObjectPtr<UAbilitySystemComponent>& ASC,
	                        const TObjectPtr<UAttributeSet>& AS)
		: PlayerController(PC),
		  PlayerState(PS),
		  AbilitySystemComponent(ASC),
		  AttributeSet(AS)
	{
	}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState;	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;
};

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;	

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
