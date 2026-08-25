// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	

	
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AAuraCharacter::InitAbilityInfo()
{
	if (AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>())
	{
		if (AuraPlayerState->GetAbilitySystemComponent())
		{
			AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
		}
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
		AttributeSetClass = Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet());
		if (AbilitySystemComponent)
		{
			Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
			InitializeDefaultAttributes();
		
		}
		if (AAuraPlayerController*AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
		{
			if (AAuraHUD*AuraHUD = AuraPlayerController->GetHUD<AAuraHUD>())
			{
				AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSetClass);
			}
		}
	
	
	
	}
	
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityInfo();
	
}

int32 AAuraCharacter::GetLevel()
{
	return GetPlayerState<AAuraPlayerState>()->GetLevel();
}
