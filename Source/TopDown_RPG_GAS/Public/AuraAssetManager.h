// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_RPG_GAS_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UAuraAssetManager& Get();
	
	virtual void StartInitialLoading() override;
};
