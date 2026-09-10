// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/EnemyHealthBarWidget.h"

AEnemyCharacter::AEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSetClass = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSetClass"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(120.f, 12.f));
	HealthBar->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	HealthBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthBar->SetVisibility(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AEnemyCharacter::InitAbilityInfo()
{
	Super::InitAbilityInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	if(HasAuthority())
	InitializeDefaultAttributes();
	
	
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityInfo();
	
	if (UEnemyHealthBarWidget* HealthBarWidget = Cast<UEnemyHealthBarWidget>(HealthBar->GetUserWidgetObject()))
	{
		HealthBarWidget->SetWidgetController(this);
	}
	BindHealthBarCallbacks();
	UpdateHealthBar();
                       
}

void AEnemyCharacter::Highlight() 
{
	bHighlighted = true;
	HealthBar->SetVisibility(true);
	
}

void AEnemyCharacter::UnHighlight() 
{
	bHighlighted = false;
	HealthBar->SetVisibility(false);
}

int32 AEnemyCharacter::GetLevel()
{
	return EnemyLevel;
}

void AEnemyCharacter::BindHealthBarCallbacks()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSetClass);
	if (!AbilitySystemComponent || !AuraAttributeSet)
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData&)
		{
			UpdateHealthBar();
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData&)
		{
			UpdateHealthBar();
		}
	);
}

void AEnemyCharacter::UpdateHealthBar()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSetClass);
	if (!HealthBar || !AuraAttributeSet)
	{
		return;
	}

	UEnemyHealthBarWidget* HealthBarWidget = Cast<UEnemyHealthBarWidget>(HealthBar->GetUserWidgetObject());
	if (!HealthBarWidget)
	{
		return;
	}

	HealthBarWidget->SetHealthValues(AuraAttributeSet->GetHealth(), AuraAttributeSet->GetMaxHealth());
}

