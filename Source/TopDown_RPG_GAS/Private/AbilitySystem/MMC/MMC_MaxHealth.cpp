// Copyright 13


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"


UMMC_MaxHealth::UMMC_MaxHealth()
{
	Vigor.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	Vigor.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	Vigor.bSnapshot = false;

	RelevantAttributesToCapture.Add(Vigor);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float VigorMagnitude = 0.f;
	GetCapturedAttributeMagnitude(Vigor, Spec, EvaluationParameters,VigorMagnitude);

	VigorMagnitude = FMath::Max<float>(VigorMagnitude, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 80.f + 2.5f * VigorMagnitude + 10.f * PlayerLevel;
}
