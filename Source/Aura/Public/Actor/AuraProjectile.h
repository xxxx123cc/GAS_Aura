// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

struct FGameplayEffectSpecHandle;
class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraProjectile();
     UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	UPROPERTY(BlueprintReadWrite)
	FGameplayEffectSpecHandle EffectSpecHandle;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UFUNCTION()
	 void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void Destroyed() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>Sound;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>LoopingSound;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent>AudioComponent;
	
	
	bool bHit=false;
	UPROPERTY(EditAnywhere)
	float LifeSpan=15.f;
	
};
