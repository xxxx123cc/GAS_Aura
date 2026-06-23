// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	OnMaxHealthUpdate.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetMaxHealth());
	OnMaxManaUpdate.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetMaxMana());
	OnHealthUpdate.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetHealth());
	OnManaUpdate.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetMana());
}