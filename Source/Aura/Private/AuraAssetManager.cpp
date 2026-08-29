// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include "AuraGamePlayTags.h"
const UAuraAssetManager& UAuraAssetManager::Get()
{
	
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	check(AuraAssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::InitializeNativeTags();
}
