// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class TOPDOWN_RPG_GAS_API UBTService_FindNearestPlayer : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
