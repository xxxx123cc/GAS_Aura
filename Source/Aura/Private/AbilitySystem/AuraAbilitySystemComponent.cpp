// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGamePlayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&ThisClass::ClientEffectApplied_Implementation);
	
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
		if (!AbilityClass)
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilityClass, Level);
		AbilitySpec.SourceObject = InAvatarActor;
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->GetAbilityTag());
		}
		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::OnPressed(const FGameplayTag& GameplayTag)
{
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(GameplayTag))
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
		
		
		
	}
	
	
	
}

void UAuraAbilitySystemComponent::OnReleased(const FGameplayTag& GameplayTag)
{
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(GameplayTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
		
	}
	
	
}

void UAuraAbilitySystemComponent::OnTrigger(const FGameplayTag& GameplayTag)
{
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(GameplayTag))
		{  AbilitySpecInputPressed( AbilitySpec);
			if (!AbilitySpec.IsActive())
				TryActivateAbility(AbilitySpec.Handle);
		}
		
	}
	
}


void UAuraAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const
{
	FGameplayTagContainer GameplayTagContainer;
 	SpecApplied.GetAllAssetTags(GameplayTagContainer);
 	UE_LOG(LogTemp, Warning, TEXT("[EffectApplied] broadcast %d tags"), GameplayTagContainer.Num());
 	OnEffectAssetTags.Broadcast(GameplayTagContainer);     
}


	
	
}
