// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "DebuffNiagaraComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN_RPG_GAS_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	UDebuffNiagaraComponent();

	UPROPERTY(VisibleAnywhere)
	FGameplayTag DebuffTag;

protected:
	virtual void BeginPlay() override;
	void DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
