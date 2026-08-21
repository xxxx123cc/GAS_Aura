 // Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraUserWidget.h"

#include "UI/WidgetController/AuraWidgetController.h"

 void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
 {
 	WidgetController=InWidgetController;
 	//获得控制器后通过控制器绑定委托
 	WidgetControllerSet();
 	
 }
