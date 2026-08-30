// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributesMenuWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAuraAttributeChanged,FAuraAttributeInfo,AttributeInfo);

UCLASS(BlueprintType,Blueprintable)
class AURA_API UAttributesMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	
	virtual void BroadcastInitialValues() override;
	
	virtual void BindCallBacksToDelegate() override;
	
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAuraAttributeChanged OnAuraAttributeChanged;
	
	
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="GAS|Attributes")
	TObjectPtr<UAttributeInfo> AttributeInfo;
	
	
	
	
private:
	
	
	
};
