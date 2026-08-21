// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{	
	GENERATED_BODY()
	
public:
	//为控件蓝图设置一个控件控制器
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController );
	//蓝图控件控制器
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject>WidgetController;
	
protected:
	//控件控制器被设置时触发
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
	
};
