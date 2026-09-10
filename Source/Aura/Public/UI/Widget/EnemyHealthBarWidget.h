// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/AuraUserWidget.h"
#include "EnemyHealthBarWidget.generated.h"

class UProgressBar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEnemyHealthChanged, float, Health, float, MaxHealth, float, HealthPercent);

/**
 * World-space enemy health bar widget.
 */
UCLASS()
class AURA_API UEnemyHealthBarWidget : public UAuraUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Enemy Health Bar")
	void SetHealthValues(float InHealth, float InMaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Health Bar")
	float Health = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Health Bar")
	float MaxHealth = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Health Bar")
	float HealthPercent = 1.f;

	UPROPERTY(BlueprintAssignable, Category = "Enemy Health Bar")
	FOnEnemyHealthChanged OnHealthChanged;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "Enemy Health Bar")
	TObjectPtr<UProgressBar> HealthBar;

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Health Bar")
	void HealthChanged(float NewHealth, float NewMaxHealth, float NewHealthPercent);
};
