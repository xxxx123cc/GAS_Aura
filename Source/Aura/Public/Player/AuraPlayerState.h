// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interaction/CombatInterface.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	FORCEINLINE int32 GetLevel() ;
	
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSetClass; }
	
protected:
	
	
    UPROPERTY(EditDefaultsOnly, Category = "PlayerState")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerState")
	TObjectPtr<UAttributeSet> AttributeSetClass;
	
	
	
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_PlayerLevel, Category = "PlayerState")
	int32 PlayerLevel=1;
	
	UFUNCTION()
	void OnRep_PlayerLevel(int OldPlayerLevel);
};
