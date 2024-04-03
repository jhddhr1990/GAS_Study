// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// 创建委托
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	// 在ASC上添加角色能力GA
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	// 输入操作触发GA
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputReleased(const FGameplayTag& InputTag);
protected:
	// 该函数用于接收AbilitySystemComponent组件中定义的多播委托函数的参数
	// DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameplayEffectAppliedDelegate, UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle);
	// FOnGameplayEffectAppliedDelegate OnGameplayEffectAppliedDelegateToSelf;
	// 该多播委托函数OnGameplayEffectAppliedDelegateToSelf在GE被应用于自身ASC时调用
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
