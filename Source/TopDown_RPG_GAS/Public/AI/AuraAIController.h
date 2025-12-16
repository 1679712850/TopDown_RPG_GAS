// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AuraAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class TOPDOWN_RPG_GAS_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAuraAIController();
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
