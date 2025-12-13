// Copyright 13


#include "AbilitySystem/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	auto MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	bool bIsLocalControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocalControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		auto AbilityHandle = GetAbilitySpecHandle();
		auto PredicationKey = GetActivationPredictionKey();
		AbilitySystemComponent->AbilityTargetDataSetDelegate(AbilityHandle, PredicationKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		bool bCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(AbilityHandle, PredicationKey);
		if (bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();			
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	auto PC = Ability->GetCurrentActorInfo()->PlayerController;
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false , HitResult);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetData->HitResult = HitResult;
	DataHandle.Add(TargetData);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
		);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
