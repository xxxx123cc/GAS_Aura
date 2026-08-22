// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "DynamicMesh/DynamicMesh3.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	
	const UAuraAttributeSet*AuraAttributeSet =CastChecked<UAuraAttributeSet>(AttributeSet);
	OnMaxHealthUpdate.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnMaxManaUpdate.Broadcast(AuraAttributeSet->GetMaxMana());
	OnHealthUpdate.Broadcast(AuraAttributeSet->GetHealth());
	OnManaUpdate.Broadcast(AuraAttributeSet->GetMana());
	
	
	
}

void UOverlayWidgetController::BindCallBacksToDelegate()
{
	Super::BindCallBacksToDelegate();
	const UAuraAttributeSet*AuraAttributeSet =CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthUpdate.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthUpdate.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaUpdate.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaUpdate.Broadcast(Data.NewValue);
	});
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->OnEffectAssetTags.AddLambda(
	[this](FGameplayTagContainer EffectTags)
	{
		for (const FGameplayTag& GameplayTag : EffectTags)
		{
			if (!GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
			{
				continue;
			}
			UE_LOG(LogTemp, Warning, TEXT("[Lambda] matched Message tag: %s, DataTable valid=%d"), *GameplayTag.ToString(), UIWidgetDataTable != nullptr);

			const FUIWidgetRow *WidgetRow=GetTableRowByTag<FUIWidgetRow>(GameplayTag,UIWidgetDataTable);
			if (WidgetRow)
			{
				UE_LOG(LogTemp, Warning, TEXT("[Lambda] broadcasting row: %s"), *GameplayTag.ToString());
				OnMessageWidgetRow.Broadcast(*WidgetRow);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[Lambda] row NOT found for: %s"), *GameplayTag.ToString());
			}

		}
		
	}	
	);

}

