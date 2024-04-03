// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

struct FGameplayTag;
// 储存有InputAction和FGameplayTag的结构体，方便添加不用的操作和Tag对应
USTRUCT(Blueprintable)
struct FAuraInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	// 根据Tag查找UInputAction
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	// 在蓝图中添加输入配置
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;
};
