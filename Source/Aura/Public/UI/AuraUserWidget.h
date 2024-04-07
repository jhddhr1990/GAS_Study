// JHDDHR

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
	// UI的控制器
	UPROPERTY(BlueprintReadOnly, Category = "JHD")
	TObjectPtr<UObject> WidgetController;
	// 设置UI的控制器
	UFUNCTION(BlueprintCallable, Category = "JHD")
	void SetWidgetController(UObject* InWidgetController);
	
protected:
	// 在C++中执行此函数，蓝图中调用的一起被执行
	UFUNCTION(BlueprintImplementableEvent, Category = "JHD")
	void IsControllerSet();
};
