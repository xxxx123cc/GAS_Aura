// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntellectDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntellectDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntellectDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(IntellectDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	float Intellect = 0.f;
	GetCapturedAttributeMagnitude(IntellectDef, Spec, EvaluateParameters ,Intellect);
	Intellect = FMath::Max(Intellect, 0.f);
	
	ICombatInterface *CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level =CombatInterface->GetLevel();
	
	
	
	return 50 + 2.5 * Intellect + 15 * Level;
	
	
}
