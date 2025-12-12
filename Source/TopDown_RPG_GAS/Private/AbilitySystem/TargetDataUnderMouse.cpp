// Copyright 13


#include "AbilitySystem/TargetDataUnderMouse.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	auto MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	auto PC = Ability->GetCurrentActorInfo()->PlayerController;
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false , HitResult);
	if (HitResult.bBlockingHit)
	{
		ValidData.Broadcast(HitResult.Location);
	}
}
