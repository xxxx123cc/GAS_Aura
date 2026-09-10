// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/AuraPlayerController.h"


void UAuraProjectileSpell::SpawnFireBolt(const FVector& TargetLocation)
{
	const bool bIsServer =HasAuthority(&GetCurrentActivationInfoRef());
	if (bIsServer)
	{
		
		ICombatInterface *CombatInterface=Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
		AActor* AvatarActor = GetAvatarActorFromActorInfo();
		
		if (CombatInterface && AvatarActor)
		{
			FVector FacingDirection = TargetLocation - AvatarActor->GetActorLocation();
			FacingDirection.Z = 0.f;
			// if (!FacingDirection.IsNearlyZero())
			// {
			// 	AvatarActor->SetActorRotation(FacingDirection.Rotation());
			// }
			
			const FVector SpawnLocation = CombatInterface->GetWeaponSocket();
			FTransform Transforms;
			Transforms.SetLocation(SpawnLocation);
		     
			FVector Target =TargetLocation;
			FVector Direction=Target-SpawnLocation;
			Direction.Normalize();
			Transforms.SetRotation(Direction.Rotation().Quaternion());
			AActor* TargetActor =AvatarActor;
			APawn*Instigator=   Cast<APawn>(AvatarActor) ;
			AAuraProjectile*Projectile= GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,Transforms,TargetActor,Instigator,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			
			UAbilitySystemComponent*ASC=GetAbilitySystemComponentFromActorInfo();
		 	Projectile->EffectSpecHandle=ASC->MakeOutgoingSpec(DamageClass,GetAbilityLevel(),ASC->MakeEffectContext());
			Projectile->FinishSpawning(Transforms);
		 	
			
		 	
		}
		
	}
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	
	
}
