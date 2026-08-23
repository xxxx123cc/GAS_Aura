// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::InitAbilityInfo()
{
}

void AAuraCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitializeDefaultAttributes()const
{
	
	if (UAuraAbilitySystemComponent*ASC =Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		
		const FGameplayEffectContextHandle EffectContextHandle=ASC->MakeEffectContext();	
		
		const FGameplayEffectSpecHandle EffectSpecHandle=ASC->MakeOutgoingSpec(DefaultAttributes,1,EffectContextHandle);
			
		ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),ASC);
	}
}


