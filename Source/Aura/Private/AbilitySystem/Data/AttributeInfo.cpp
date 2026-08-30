// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoFromTag(FGameplayTag Tag) const
{
	for (const auto& AttributeInfo : AttributeInfos )
	{
		if (AttributeInfo.AttributeTag.MatchesTagExact(Tag))
		{
			return AttributeInfo;
		}
		
	}
	
	return FAuraAttributeInfo();
}
