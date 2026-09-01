// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "AuraEnhancedInputComponent.generated.h"

class UAuraInputConfig;
/**
 * 
 */
UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass,typename CallBackFun>
	void BindAbilityActions(const UAuraInputConfig* InputConfig,UserClass*User,CallBackFun Pressed,CallBackFun Released,CallBackFun Trigger);
	
};

template <typename  UserClass, typename CallBackFun>
void UAuraEnhancedInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* User,
	 CallBackFun Pressed, CallBackFun Released,CallBackFun Trigger)
{
    check(InputConfig);
	for (const FAuraInputAction& AuraInputAction:InputConfig->AbilityInputActions )
	{
		
		BindAction(AuraInputAction.InputAction,ETriggerEvent::Started,User,Pressed,AuraInputAction.InputTag);
		BindAction(AuraInputAction.InputAction,ETriggerEvent::Completed,User,Released,AuraInputAction.InputTag);
		BindAction(AuraInputAction.InputAction,ETriggerEvent::Triggered,User,Trigger,AuraInputAction.InputTag);
	}
}
