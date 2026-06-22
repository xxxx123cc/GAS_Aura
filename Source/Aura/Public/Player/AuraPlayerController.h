// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

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
	//移动输入
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	
	
	TObjectPtr<IEnemyInterface>LastActor = nullptr;
	
	
	TObjectPtr<IEnemyInterface>HitActor = nullptr;
	
	void MoveInputAction(const FInputActionValue& Value);
	
	
};
