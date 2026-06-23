// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	
	if (OverlayWidgetController==nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlapWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		
	return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PlayerState, UAbilitySystemComponent* Asc,
                           UAttributeSet* AttributeSet)
{
	
	UUserWidget* Widget =CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget =Cast<UAuraUserWidget>(Widget);
	
	const FWidgetControllerParams Params(PC,PlayerState,Asc,AttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);
	
	OverlayWidget->SetWidgetController(WidgetController);
	
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	

}
