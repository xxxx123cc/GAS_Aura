// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FGameplayTag AttributeTag=FGameplayTag();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FText AttributeName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FText AttributeDescription;
	UPROPERTY( BlueprintReadOnly, Category = "Attribute")
	float BaseValue=0.f;
};

/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
	
	
public:
	
	FAuraAttributeInfo FindAttributeInfoFromTag(FGameplayTag Tag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	TArray<FAuraAttributeInfo> AttributeInfos;
};
