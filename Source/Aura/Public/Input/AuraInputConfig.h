// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

/**
 * 
 */


class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputAction")
	TObjectPtr<UInputAction> InputAction=nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputTag")
	FGameplayTag InputTag=FGameplayTag();
	
	
};


UCLASS(BlueprintType,Blueprintable)
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputConfig")
	TArray<FAuraInputAction>AbilityInputActions;
	
	
	UFUNCTION(BlueprintCallable,Category="InputConfig")
	UInputAction* FindInputActionForTag(FGameplayTag& InputTag) const  ;
	
	
};
