// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	// 用来根据输入的Tag，决定是否触发GA
	UPROPERTY(EditDefaultsOnly, Category = "JHD")
	FGameplayTag StartupInputTag;
};
