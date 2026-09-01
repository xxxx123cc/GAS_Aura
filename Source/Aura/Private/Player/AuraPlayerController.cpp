// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Character/AuraCharacterBase.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Input/AuraInputConfig.h"
#include "Interaction/EnemyInterface.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerController::AAuraPlayerController()
{
	
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DefaultMappingContext);
	check(AbilityInputMappingContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	Subsystem->AddMappingContext(AbilityInputMappingContext, 0);

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraEnhancedInputComponent*AuraEnhancedInputComponent=CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	
	AuraEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::MoveInputAction);
   
	AuraEnhancedInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputActionPressed,&ThisClass::AbilityInputActionOnCompleted,&AAuraPlayerController::AbilityInputActionOnTrigger);
	
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	
}

void AAuraPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	//上一个物体
	LastActor = HitActor;
	//当前物体
	HitActor = HitResult.GetActor() ? Cast<IEnemyInterface>(HitResult.GetActor()) : nullptr;
	//上个和这个相同则不做处理
	if (HitActor == LastActor)
	return;
	//当前物体有效则高亮
	if (HitActor)
	{
		HitActor->Highlight();
		
	}
	//上个物体有效当前物体无效则取消上个物体高亮
	if (LastActor)
		LastActor->UnHighlight();
	
	
	
	
	
}

void AAuraPlayerController::MoveInputAction(const FInputActionValue& Value) const
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr) return;
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	
}

void AAuraPlayerController::AbilityInputActionPressed(FGameplayTag GameplayTag) const
{
	
		AbilitySystemComponent->OnPressed(GameplayTag);
	
}

void AAuraPlayerController::AbilityInputActionOnCompleted( FGameplayTag GameplayTag) const
{
	
		AbilitySystemComponent->OnReleased(GameplayTag);
	
}

void AAuraPlayerController::AbilityInputActionOnTrigger(FGameplayTag GameplayTag) const
{
	
		AbilitySystemComponent->OnTrigger(GameplayTag);
	
}
