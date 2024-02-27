// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;

USTRUCT(Blueprintable)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
    // 对应Tag，方便查找
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	// 需要显示的文本信息
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	// 需要生成的UI类
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	// 显示图标
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

// 属性委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewAttribute);
// UI信息委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, UIWidgetRow);


/**
 * 
 */
UCLASS()
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitalValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(EditDefaultsOnly, Category = "JHD")
	TObjectPtr<UDataTable> MessageDataTable;
	
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnAttributeChangedSignature OnHealChanged;
	
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnAttributeChangedSignature OnMaxHealChanged;

	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnAttributeChangedSignature OnMaxManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FMessageWidgetRowSignature MessageWidgetDelegate;
protected:
	// 用于使用GameplayTag为条件，在上面创建的数据表中找到该行信息
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
