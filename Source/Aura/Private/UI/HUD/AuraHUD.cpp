// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributesMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	//OverlayWidgetController存在直接返回，不存在就新建一个
	if (OverlayWidgetController==nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlapWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallBacksToDelegate();
	    return OverlayWidgetController;
	}
	return OverlayWidgetController;
	

}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PlayerState, UAbilitySystemComponent* Asc,
                           UAttributeSet* AttributeSet)
{
	//根据蓝图设置的控件蓝图类创建widget
	UUserWidget* Widget =CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	//转化为需要的类型
	OverlayWidget =Cast<UAuraUserWidget>(Widget);
	//设置需要的类
	const FWidgetControllerParams Params(PC,PlayerState,Asc,AttributeSet);
	//获得界面控制器
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);
	//将得到的widgetcontroller赋值给控件蓝图的widgetcontroller
	OverlayWidget->SetWidgetController(WidgetController);
	
	//控件蓝图获得控制器后才能绑定控制器里的委托，然后才能广播初始值进行初始化
	WidgetController->BroadcastInitialValues();
	//控件蓝图添加视口
	Widget->AddToViewport();
}

UAttributesMenuWidgetController* AAuraHUD::GetAttributesMenuWidgetController(const FWidgetControllerParams& Params)
{
	if (AttributesMenuWidgetController==nullptr)
	{
		AttributesMenuWidgetController = NewObject<UAttributesMenuWidgetController>(this,AttributesMenuWidgetControllerClass);
		AttributesMenuWidgetController->SetWidgetControllerParams(Params);
		AttributesMenuWidgetController->BindCallBacksToDelegate();
		return AttributesMenuWidgetController;
	}
	return AttributesMenuWidgetController;
	
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	

}
