// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGamePlayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&ThisClass::EffectApplied);
	
	FAuraGameplayTags GameplayTag= FAuraGameplayTags::Get();

	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("Attributes_Secondary_Armor tag name: %s"),*GameplayTag.Attributes_Secondary_Armor.GetTagName().ToString()));
}

void UAuraAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const
{
	FGameplayTagContainer GameplayTagContainer;
	SpecApplied.GetAllAssetTags(GameplayTagContainer);
	UE_LOG(LogTemp, Warning, TEXT("[EffectApplied] broadcast %d tags"), GameplayTagContainer.Num());
	OnEffectAssetTags.Broadcast(GameplayTagContainer);                                      
	
	
	
}
