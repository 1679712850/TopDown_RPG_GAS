// Copyright 13


#include "Input/AuraInputConfig.h"

UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	for (const auto& AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputAction && AbilityInputAction.InputTag == InputTag)
		{
			return AbilityInputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
