// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGamePlayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&ThisClass::EffectApplied);
	
	FAuraGameplayTags GameplayTag= FAuraGameplayTags::Get();
	
}

void UAuraAbilitySystemComponent::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilityClasses, int32 Level, AActor* InAvatarActor)
{
	if (!InAvatarActor)
	{
		return;
	}

	for (TSubclassOf<UGameplayAbility>& AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass, Level);
		AbilitySpec.SourceObject = InAvatarActor;
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
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
