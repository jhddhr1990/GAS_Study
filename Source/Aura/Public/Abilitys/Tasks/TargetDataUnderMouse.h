// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FVector&, Data);
/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
	// 该静态函数用于返回实例化和初始化的Task
	UFUNCTION(BlueprintCallable, Category = "JHD|Tasks", meta = (DisplayName= "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	// 该委托使得在蓝图调用该TASK时，生成引脚获得ValidData，此为异步操作
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;
protected:
	virtual void Activate() override;
};
