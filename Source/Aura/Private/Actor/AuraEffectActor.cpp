// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
	
	
	
	
	// MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	// SetRootComponent(MeshComponent);
	// SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// SphereComponent->SetupAttachment(MeshComponent);

}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	// SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	// SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}

void AAuraEffectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(RemovalTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantApplyPolicy == EEffectApplyPolicy::ApplyOnOverLap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplyPolicy == EEffectApplyPolicy::ApplyOnOverLap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteApplyPolicy == EEffectApplyPolicy::ApplyOnOverLap)
	{
		GetWorldTimerManager().ClearTimer(RemovalTimerHandle);
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (bDestroyOnEffectRemoval)
	{     Destroy();
	}
	
}

void AAuraEffectActor::EndOverlap(AActor* TargetActor)
{
	if (InstantApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if ( RemovePolicy == EEffectRemovePolicy::RemoveOnEndOverLap)
	{
		if (EffectRemovalDelay > 0.f)
		{
			GetWorldTimerManager().SetTimer(
				RemovalTimerHandle,
				FTimerDelegate::CreateLambda([this, TargetActor]()
				{
					if (IsValid(this) && IsValid(TargetActor))
					{
						RemoveEffect(TargetActor);
					}
				}),
				EffectRemovalDelay, false);
		}
		else
		{
			RemoveEffect(TargetActor);
		}
	}
	
	
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(Target);
	if (Interface)
	{
		UAuraAbilitySystemComponent* AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(Interface->GetAbilitySystemComponent());
		if (AbilitySystemComponent && GameplayEffectClass)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				const bool bIsInfinite = SpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
				if (bIsInfinite && RemovePolicy == EEffectRemovePolicy::RemoveOnEndOverLap)
					ActiveEffectHandles.Add(ActiveEffectHandle, AbilitySystemComponent);
			}
			
			
			
		}
	}
	
	
}

void AAuraEffectActor::RemoveEffect(AActor* Targets)
{
	IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(Targets);
	if (Interface)
	{
		UAuraAbilitySystemComponent* AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(Interface->GetAbilitySystemComponent());
		if (!AbilitySystemComponent) 
			return;
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto& Pair : ActiveEffectHandles)
		{
			if (Pair.Value == AbilitySystemComponent)
			{
				AbilitySystemComponent->RemoveActiveGameplayEffect(Pair.Key,1);
				HandlesToRemove.Add(Pair.Key);
			
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
		
		
	}
	
	
	
}

// void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent,
// 	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
// 	const FHitResult& SweepResult)
// {
//
// 	if (IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(OtherActor))
// 	{
// 		UAuraAbilitySystemComponent* AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(Interface->GetAbilitySystemComponent());
//
// 		const UAuraAttributeSet* Attributes = AbilitySystemComponent->GetSet<UAuraAttributeSet>();
// 		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(Attributes);
// 		MutableAuraAttributeSet->SetHealth(Attributes->GetHealth() + 25.f);
// 		MutableAuraAttributeSet->SetMana(Attributes->GetMana() - 25.f);
// 		Destroy();
// 	}
//
// }
//
// void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent,
// 	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
//
// }
