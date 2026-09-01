// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

UInputAction* UAuraInputConfig::FindInputActionForTag(FGameplayTag &InputTag) const
{
	for (const FAuraInputAction&  InputAction:AbilityInputActions )
	{
		if (InputAction.InputTag.IsValid()&&InputAction.InputTag==InputTag)
		{
			return InputAction.InputAction;
		}
	}
	return nullptr;
}
