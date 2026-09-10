// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/EnemyHealthBarWidget.h"

#include "Components/ProgressBar.h"

void UEnemyHealthBarWidget::SetHealthValues(float InHealth, float InMaxHealth)
{
	Health = FMath::Max(0.f, InHealth);
	MaxHealth = FMath::Max(0.f, InMaxHealth);
	HealthPercent = MaxHealth > 0.f ? FMath::Clamp(Health / MaxHealth, 0.f, 1.f) : 0.f;

	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercent);
	}

	OnHealthChanged.Broadcast(Health, MaxHealth, HealthPercent);
	HealthChanged(Health, MaxHealth, HealthPercent);
}
