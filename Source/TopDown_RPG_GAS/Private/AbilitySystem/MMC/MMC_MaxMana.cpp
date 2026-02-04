// Copyright 13


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	Intelligence.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	Intelligence.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	Intelligence.bSnapshot = false;

	RelevantAttributesToCapture.Add(Intelligence);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float IntelligenceMagnitude = 0.f;
	GetCapturedAttributeMagnitude(Intelligence, Spec, EvaluationParameters,IntelligenceMagnitude);

	IntelligenceMagnitude = FMath::Max<float>(IntelligenceMagnitude, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	
	return 50.f + 2.5f * IntelligenceMagnitude + 15.f * PlayerLevel;
}
