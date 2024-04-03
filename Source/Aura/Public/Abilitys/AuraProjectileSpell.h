// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Abilitys/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()
protected:
	// 重写激活技能时调用的函数
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	// 该变量用于设置生成的投射物类，如火球术等
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
