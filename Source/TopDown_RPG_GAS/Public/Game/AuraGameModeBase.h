// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
};
