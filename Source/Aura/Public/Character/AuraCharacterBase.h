// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;


UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void InitAbilityInfo();
	
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSetClass; }
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	virtual int32  GetLevel() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Character|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TObjectPtr<UAttributeSet> AttributeSetClass;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Character|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalEffect;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level = 1.f) const;
	
	void InitializeDefaultAttributes()const;
	
	
	
};
