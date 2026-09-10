// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "Character/AuraCharacter.h"
#include "Player/AuraPlayerController.h"



UTargetDataUnderMouse* UTargetDataUnderMouse::TargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	
	const bool bIsLocalController=Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocalController)
		SendMouseCursorData();
	else
	{
		FGameplayAbilitySpecHandle Handle=GetAbilitySpecHandle();
		FPredictionKey PredictionKey=GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(Handle,PredictionKey).
		AddUObject(this,&UTargetDataUnderMouse::OnTargetDataReplicatedCallBack);
		const bool bCalledDelegate= AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(Handle,PredictionKey);
		if (!bCalledDelegate)
		{
	      SetWaitingOnRemotePlayerData();		
		}
	}
	
	
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{ 
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
    AAuraPlayerController* PlayerController=Cast<AAuraPlayerController>( Ability->GetCurrentActorInfo()->PlayerController.Get());
 	FHitResult Target ;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Target);
	
	
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetData->HitResult=Target;
	
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle.Add(TargetData);
	
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetDataHandle,FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTargetDataHandle.Broadcast(TargetDataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallBack(
	const FGameplayAbilityTargetDataHandle& TargetDataReplicatedData, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTargetDataHandle.Broadcast(TargetDataReplicatedData);
	}
}


