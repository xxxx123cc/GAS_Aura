// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSetClass = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSetClass"));
	
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AEnemyCharacter::InitAbilityInfo()
{
	Super::InitAbilityInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityInfo();
                       
}

void AEnemyCharacter::Highlight() 
{
	bHighlighted = true;
	
}

void AEnemyCharacter::UnHighlight() 
{
	bHighlighted = false;
}

int32 AEnemyCharacter::GetLevel()
{
	return EnemyLevel;
}

