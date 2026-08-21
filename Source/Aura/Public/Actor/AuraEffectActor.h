// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "TimerManager.h"
#include "AuraEffectActor.generated.h"


class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class  EEffectApplyPolicy:uint8
{
       ApplyOnOverLap,
       ApplyOnEndOverLap,
       NotApply
	
};

UENUM(BlueprintType)
enum class  EEffectRemovePolicy:uint8
{
	RemoveOnEndOverLap,
	NotRemove
	
};




UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraEffectActor();

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable,Category="Effect")
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable,Category="Effect")
	void EndOverlap(AActor* TargetActor);
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EEffectApplyPolicy InstantApplyPolicy = EEffectApplyPolicy::NotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EEffectApplyPolicy DurationApplyPolicy = EEffectApplyPolicy::NotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EEffectApplyPolicy InfiniteApplyPolicy = EEffectApplyPolicy::NotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EEffectRemovePolicy RemovePolicy = EEffectRemovePolicy::NotRemove;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	float EffectRemovalDelay = 1.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	float ActorLevel=1.f;
	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;
	FTimerHandle RemovalTimerHandle;
	
	
	UFUNCTION(BlueprintCallable,Category="Effect")
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable,Category="Effect")
	void RemoveEffect(AActor* Target);
	
	
	
	
	//UFUNCTION()
	//virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//UPROPERTY(EditAnywhere,Category="Componment")
	//TObjectPtr<UStaticMeshComponent>MeshComponent;
	//UPROPERTY(EditAnywhere,Category="Componment")
	//TObjectPtr<USphereComponent>SphereComponent;
	
	
};
