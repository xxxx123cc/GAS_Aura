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
	GameplayTags.Attributes_Secondary_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), TEXT("最大生命"));
	GameplayTags.Attributes_Secondary_MaxMana= GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), TEXT("最大法力"));
	
	//Primary GameplayTags
	
	GameplayTags.Attributes_Primary_Strength = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), TEXT("力量"));
	GameplayTags.Attributes_Primary_Intelligence = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), TEXT("智力"));
	GameplayTags.Attributes_Primary_Resilience= GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), TEXT("韧性"));	
	GameplayTags.Attributes_Primary_Vigor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), TEXT("活力"));
	
	//Abilities GameplayTags
	GameplayTags.InputTag_LMB = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag_LMB"),TEXT("鼠标左键"));
	GameplayTags.InputTag_RMB = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag_RMB"),TEXT("鼠标右键"));
	GameplayTags.InputTag_1 = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag_1"),TEXT("键位1"));
	GameplayTags.InputTag_2 = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag_2"),TEXT("键位2"));
	GameplayTags.InputTag_3 = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag_3"),TEXT("键位3"));
	GameplayTags.InputTag_4 = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag_4"),TEXT("键位4"));
}

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
