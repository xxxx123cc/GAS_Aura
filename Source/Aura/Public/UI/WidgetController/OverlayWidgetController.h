// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate,float,Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthUpdate,float,MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaUpdate,float,Mana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaUpdate,float,MaxMana);
/**
 * 
 */
UCLASS()
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthUpdate OnHealthUpdate;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaUpdate  OnManaUpdate;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthUpdate OnMaxHealthUpdate;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaUpdate  OnMaxManaUpdate;
	
	
protected:
	
	
private:
	
	
	
};
