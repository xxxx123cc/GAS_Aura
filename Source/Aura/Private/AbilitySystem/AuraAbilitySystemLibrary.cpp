// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	check(PlayerController);
	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
	{
		AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
		UAuraAbilitySystemComponent* AuraASC = AuraPlayerState ? Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent()) : nullptr;
		UAuraAttributeSet* AuraAttributeSet = AuraPlayerState ? Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet()) : nullptr;
		 FWidgetControllerParams Params(PlayerController, AuraPlayerState, AuraASC, AuraAttributeSet);
		return AuraHUD->GetOverlayWidgetController(Params);
	}
	return nullptr;
}

UAttributesMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeInfoWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	check(PlayerController);
	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
	{
		AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
		UAuraAbilitySystemComponent* AuraASC = AuraPlayerState ? Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent()) : nullptr;
		UAuraAttributeSet* AuraAttributeSet = AuraPlayerState ? Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet()) : nullptr;
		 FWidgetControllerParams Params(PlayerController, AuraPlayerState, AuraASC, AuraAttributeSet);
		return AuraHUD->GetAttributesMenuWidgetController(Params);
	}
	return nullptr;
	
	
}
