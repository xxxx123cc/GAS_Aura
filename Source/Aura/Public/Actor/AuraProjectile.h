// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

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
     UPROPERTY()
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	UPROPERTY()
	TObjectPtr<UNiagaraSystem> ParticleSystemComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UFUNCTION()
	 void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	
	
};
