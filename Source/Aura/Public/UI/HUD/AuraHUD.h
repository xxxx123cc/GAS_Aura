// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UOverlayWidgetController;
class UAuraWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	//初始化界面
	void InitOverlay(APlayerController*PC,APlayerState* PlayerState,UAbilitySystemComponent*Asc,UAttributeSet* AttributeSet);
	
	
	

protected:
	
	virtual void BeginPlay() override;
	
	
private:
	
	UPROPERTY()
	TObjectPtr<UAuraUserWidget>OverlayWidget;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;
	
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	TSubclassOf<UUserWidget>OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly,Category="WidgetController")
	TSubclassOf<UAuraWidgetController>OverlapWidgetControllerClass;
};
