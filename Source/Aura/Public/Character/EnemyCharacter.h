// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
	public:
	AEnemyCharacter();
	
    protected:
	
	virtual void InitAbilityInfo() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void BeginPlay() override;
	//Enemy Interface
	virtual void Highlight()  override;
	
	virtual void UnHighlight()  override;
	//Enemy Interface
	
	//Combat Interface
	virtual int32 GetLevel() override;
	//Combat Interface
	
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = "Enemy")
	bool bHighlighted = false;
	
private:
	UPROPERTY(VisibleAnywhere,Category = "Enemy")
	int32 EnemyLevel = 1;
};
