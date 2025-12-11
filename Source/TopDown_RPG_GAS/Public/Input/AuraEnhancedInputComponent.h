// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN_RPG_GAS_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraEnhancedInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	for (const auto& AbilityInputAction : InputConfig->AbilityInputActions)
	{
		if (AbilityInputAction.InputAction && AbilityInputAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AbilityInputAction.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AbilityInputAction.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(AbilityInputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AbilityInputAction.InputTag);
			}
		}
	}
}
