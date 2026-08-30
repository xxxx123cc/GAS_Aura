// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributesMenuWidgetController.h"

#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributesMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AS || !AttributeInfo || !AbilitySystemComponent)
	{
		return;
	}

	const auto BroadcastAttribute = [this](const FGameplayTag& Tag, const float Value)
	{
		if (!AttributeInfo)
		{
			return;
		}

		FAuraAttributeInfo Attribute = AttributeInfo->FindAttributeInfoFromTag(Tag);
		Attribute.BaseValue = Value;
		OnAuraAttributeChanged.Broadcast(Attribute);
 	};
  	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Primary_Strength, AS->GetStrength());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Primary_Intelligence, AS->GetIntelligence());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Primary_Resilience, AS->GetResilience());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Primary_Vigor, AS->GetVigor());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_Armor, AS->GetArmor());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_ArmorPenetration, AS->GetArmorPenetration());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_BlockChance, AS->GetBlockChance());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitChance, AS->GetCriticalHitChance());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitDamage, AS->GetCriticalHitDamage());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitResistance, AS->GetCriticalHitResistance());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_HealthRegeneration, AS->GetHealthRegeneration());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_ManaRegeneration, AS->GetManaRegeneration());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_MaxHealth, AS->GetMaxHealth());
	BroadcastAttribute(FAuraGameplayTags::Get().Attributes_Secondary_MaxMana, AS->GetMaxMana());
}

void UAttributesMenuWidgetController::BindCallBacksToDelegate()
{
	Super::BindCallBacksToDelegate();
	
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AS || !AttributeInfo || !AbilitySystemComponent)
	{
		return;
	}

	const TArray<TPair<FGameplayTag, FGameplayAttribute>> AttributesToListen =
	{
		{ FAuraGameplayTags::Get().Attributes_Primary_Strength, AS->GetStrengthAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Primary_Intelligence, AS->GetIntelligenceAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Primary_Resilience, AS->GetResilienceAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Primary_Vigor, AS->GetVigorAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_Armor, AS->GetArmorAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_ArmorPenetration, AS->GetArmorPenetrationAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_BlockChance, AS->GetBlockChanceAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitChance, AS->GetCriticalHitChanceAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitDamage, AS->GetCriticalHitDamageAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitResistance, AS->GetCriticalHitResistanceAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_HealthRegeneration, AS->GetHealthRegenerationAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_ManaRegeneration, AS->GetManaRegenerationAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_MaxHealth, AS->GetMaxHealthAttribute() },
		{ FAuraGameplayTags::Get().Attributes_Secondary_MaxMana, AS->GetMaxManaAttribute() }
	};

	for (const TPair<FGameplayTag, FGameplayAttribute>& Pair : AttributesToListen)
	{ 
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda(
			[this, Tag = Pair.Key](const FOnAttributeChangeData& Data)
			{
				if (!AttributeInfo)
				{
					return;
				}

				FAuraAttributeInfo Attribute = AttributeInfo->FindAttributeInfoFromTag(Tag);
				Attribute.BaseValue = Data.NewValue;
				OnAuraAttributeChanged.Broadcast(Attribute);
			});
	}
}