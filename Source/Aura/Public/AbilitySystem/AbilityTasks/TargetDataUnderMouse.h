// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataDelegate,const FGameplayAbilityTargetDataHandle&, DataHandle);


UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataUnderMouse* TargetDataUnderMouse(UGameplayAbility* OwningAbility);


	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataDelegate OnTargetDataHandle;
private:

      virtual void	Activate() override;	

	
	void SendMouseCursorData();
	
	void OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& TargetDataReplicatedData, FGameplayTag ActivationTag);

};
