// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FGameplayTag;
struct FOnAttributeChangeData;
//血量和法力委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributesUpdate,float,NewValue);



USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()

   UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	FGameplayTag WidgetTag;

 UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	FText Message=FText();

  UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	TSubclassOf<UAuraUserWidget> WidgetClass;

   UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	UTexture2D* Image=nullptr;


};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,WidgetRow);
/**
 *
 */
UCLASS()
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:

 virtual void BroadcastInitialValues() override;

 virtual void BindCallBacksToDelegate() override;
 UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnHealthUpdate;
  UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate  OnManaUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnMaxHealthUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate  OnMaxManaUpdate;
	
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnStrengthUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnIntelligenceUpdate;
  UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnResilienceUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnVigorUpdate;

   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnArmorUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnArmorPenetrationUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnBlockChanceUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnCriticalHitChanceUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnCriticalHitDamageUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnCriticalHitResistanceUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnHealthRegenerationUpdate;
   UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributesUpdate OnManaRegenerationUpdate;

   UPROPERTY(BlueprintAssignable,Category="GAS|UI")
	FMessageWidgetRowSignature OnMessageWidgetRow;

 
protected:

   UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UDataTable>UIWidgetDataTable;

	template<typename T>
	T *GetTableRowByTag(const FGameplayTag& Tag,UDataTable* DataTable);

 
private:

 
};

template <typename T>
T* UOverlayWidgetController::GetTableRowByTag(const FGameplayTag& Tag, UDataTable* DataTable)
{
	if (DataTable == nullptr)
	{
		return nullptr;
	}

	//根据标签来寻找对应行
	for (const TPair<FName, uint8*>& RowPair : DataTable->GetRowMap())
	{
		T* Row = reinterpret_cast<T*>(RowPair.Value);
		if (Row && Row->WidgetTag == Tag)
		{
			return Row;
		}
	}
	return nullptr;

}