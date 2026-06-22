// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AEnemyCharacter::Highlight() 
{
	bHighlighted = true;
	
}

void AEnemyCharacter::UnHighlight() 
{
	bHighlighted = false;
}
