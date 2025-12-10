// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

UCLASS()
class TOPDOWN_RPG_GAS_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/* end Combat Interface */
private:
	virtual void InitAbilityActorInfo() override;
};
