// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGamePlayTags.h"
#include "GameplayTagsManager.h"

void FAuraGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	
	GameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), TEXT("护甲"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"), TEXT("护甲穿透"));
	GameplayTags.Attributes_Secondary_BlockChance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), TEXT("格挡几率"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"), TEXT("暴击几率"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), TEXT("暴击伤害"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), TEXT("暴击抗性"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), TEXT("生命恢复"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), TEXT("法力恢复"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), TEXT("最大生命"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), TEXT("最大法力"));
	
	//Primary GameplayTags
	
	GameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), TEXT("力量"));
	GameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), TEXT("智力"));
	GameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), TEXT("韧性"));	
	GameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), TEXT("活力"));
}

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
