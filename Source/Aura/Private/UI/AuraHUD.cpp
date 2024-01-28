// JHDDHR


#include "UI/AuraHUD.h"
#include "UI/AuraUserWidget.h"
#include "UI/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// 检查是否设置了相应的蓝图类
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass未设置"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass未设置"));

	// 创建OverlayUI
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(),OverlayWidgetClass);

	// 创建OverlayUI的控制器
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// 将控制器绑定到UI
	OverlayWidget->SetWidgetController(WidgetController);
	
	WidgetController->BroadcastInitalValues();
	WidgetController->BindCallbacksToDependencies();

	// 显示UI
	OverlayWidget->AddToViewport();
}

