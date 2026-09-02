// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGamePlayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Player/AuraPlayerState.h"


AAuraPlayerController::AAuraPlayerController()
{
	
	bReplicates = true;
	
	Spline=CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DefaultMappingContext);
	check(AbilityInputMappingContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		Subsystem->AddMappingContext(AbilityInputMappingContext, 0);
	}

	if (AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>())
	{
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (!AbilitySystemComponent)
	{
		if (AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>())
		{
			AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
				AuraPlayerState->GetAbilitySystemComponent());
		}
	}
	return AbilitySystemComponent;
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraEnhancedInputComponent*AuraEnhancedInputComponent=CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	
	AuraEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::MoveInputAction);
   
	AuraEnhancedInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputActionPressed,&ThisClass::AbilityInputActionOnCompleted,&ThisClass::AbilityInputActionOnTrigger);
	
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	
}


void AAuraPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRunning();
	
}

void AAuraPlayerController::AutoRunning()
{
	if (!bAutoRunning)
	{
		return;
	}

	APawn* ControllerPawn = GetPawn();
	if (!ControllerPawn)
	{
		bAutoRunning = false;
		return;
	}

	const FVector PawnLocation = ControllerPawn->GetActorLocation();
	const int32 SplinePointCount = Spline->GetNumberOfSplinePoints();
	if (SplinePointCount < 2)
	{
		bAutoRunning = false;
		return;
	}

	FVector Waypoint = Spline->GetLocationAtSplinePoint(
		FMath::Min(CurrentPathPoint, SplinePointCount - 1),
		ESplineCoordinateSpace::World);
	if (FVector::Dist2D(PawnLocation, Waypoint) <= AutoRunAcceptRadius)
	{
		++CurrentPathPoint;
		if (CurrentPathPoint >= SplinePointCount)
		{
			bAutoRunning = false;
			return;
		}
		Waypoint = Spline->GetLocationAtSplinePoint(
			CurrentPathPoint, ESplineCoordinateSpace::World);
	}

	const FVector Direction = (Waypoint - PawnLocation).GetSafeNormal2D();
	if (!Direction.IsNearlyZero())
	{
		ControllerPawn->AddMovementInput(Direction, 1.f);
	}
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

void AAuraPlayerController::MoveInputAction(const FInputActionValue& Value) 
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

void AAuraPlayerController::AbilityInputActionPressed(FGameplayTag GameplayTag)
{
	if (GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		IsTargeting=HitActor != nullptr;
		bAutoRunning=false;

		FHitResult Result;
		if (GetHitResultUnderCursor(ECC_Visibility, true, Result))
		{
			CachedDestination = Result.ImpactPoint;
			bHasDestination = true;
		}
	}
	
}

void AAuraPlayerController::AbilityInputActionOnCompleted( FGameplayTag GameplayTag) 
{
	UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
	if (!GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (AuraASC)
		{
			AuraASC->OnReleased(GameplayTag);
		}
		return;
	}
	if( HitActor )
	{
		if (AuraASC)
		{
			AuraASC->OnReleased(GameplayTag);
		}
	}
	else  if (FollowingTime<ShortPressedTime)
	{
		if (APawn* ControllerPawn = GetPawn())
		{
			if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				GetWorld(), ControllerPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& Point : NavigationPath->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World, true);
				}
				CurrentPathPoint = 1;
				bAutoRunning = NavigationPath->PathPoints.Num() > 1;
			}
		}
	}
	FollowingTime=0.f;
	
}

void AAuraPlayerController::AbilityInputActionOnTrigger(FGameplayTag GameplayTag)
{
	UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
	if (!GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (AuraASC)
		{
			AuraASC->OnTrigger(GameplayTag);
		}
		return;
	}
		
	if( HitActor )
	{
		if (AuraASC)
		{
			AuraASC->OnTrigger(GameplayTag);
		}
	}
	else if (!HitActor)
	{
		FollowingTime+=GetWorld()->GetDeltaSeconds();
		FHitResult Result;
		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Result))
		{
			CachedDestination=Result.ImpactPoint;
			bHasDestination = true;
		}
		if (APawn*ControllerPawn=GetPawn())
		{
			ControllerPawn->AddMovementInput((CachedDestination-ControllerPawn->GetActorLocation()).GetSafeNormal(),1.f);
			
		}
		
	}
	
}
