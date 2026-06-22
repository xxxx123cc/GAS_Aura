// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public AAuraCharacter,public IEnemyInterface
{
	GENERATED_BODY()
	
	public:
	AEnemyCharacter();
	
    protected:
	virtual void Highlight()  override;
	
	virtual void UnHighlight()  override;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = "Enemy")
	bool bHighlighted = false;
	
};
