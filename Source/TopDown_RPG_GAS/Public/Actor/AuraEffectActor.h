// Copyright 13

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class TOPDOWN_RPG_GAS_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

	UFUNCTION(BlueprintCallable)
	void ApplyEffectTo(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect" )
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect" )
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
};
