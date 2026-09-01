// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
class UAuraInputConfig;
class IEnemyInterface;
class UEnemyInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	virtual void Tick(float DeltaTime) override;
	
	void CursorTrace();
	
	
private:
	//默认映射上下文
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AbilityInputMappingContext;
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	
	
	
	//移动输入
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	
	//技能输入配置
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;
	
	
	
	TObjectPtr<IEnemyInterface>LastActor = nullptr;
	
	
	TObjectPtr<IEnemyInterface>HitActor = nullptr;
	
	void MoveInputAction(const FInputActionValue& Value) const;
	
	void AbilityInputActionPressed( FGameplayTag GameplayTag ) const;
	
	void AbilityInputActionOnCompleted(FGameplayTag GameplayTag) const;
	
	void AbilityInputActionOnTrigger(FGameplayTag GameplayTag) const;
};
