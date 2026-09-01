// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,FGameplayTagContainer/*资产标签*/);
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	

	void AbilityActorInfoSet();
	
	void GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilityClasses, int32 Level, AActor* InAvatarActor);
	
	void OnPressed(const FGameplayTag&GameplayTag );
	
	void OnReleased(const FGameplayTag&GameplayTag );
	
	
	void OnTrigger(const FGameplayTag&GameplayTag );
	FEffectAssetTags OnEffectAssetTags;
	
	
	
protected:
	
	virtual void BeginPlay() override;
	
	
	
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) const;
	
	
	
};
