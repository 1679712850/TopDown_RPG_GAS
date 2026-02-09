// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircle.generated.h"

UCLASS()
class TOPDOWN_RPG_GAS_API AMagicCircle : public AActor
{
	GENERATED_BODY()

public:	
	AMagicCircle();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UDecalComponent> MagicCircleDecal;
};
