// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
		
	AAuraCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	
	virtual int32 GetLevel()override;

	virtual void BeginPlay() override;
protected:
	virtual FVector GetTargetLocation() override;


	
private:
	
	
	
	virtual  void InitAbilityInfo()override;
	
	
	
};
