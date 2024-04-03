// JHDDHR


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "Abilitys/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

// 在ASC上添加角色能力GA
void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : Abilities)
	{
		// FGameplayAbilitySpec:可激活的能力规范，托管在能力系统组件上。这既定义了功能是什么（什么类、什么级别、输入绑定等），
		// 也保留了必须保持在被实例化/激活的功能之外的运行时状态。
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			// 添加复制的可选能力Tag。这些Tag也被应用的GE捕获为源Tag。
			AbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->StartupInputTag);
			//GiveAbilityAndActivateOnce(AbilitySpec); 赋予能力并同时激活能力
			GiveAbility(AbilitySpec);// 赋予能力 可以准备被激活
		}
		
	}
}
// 按住操作
void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	// 遍历所有 可以被激活的能力
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// 当该能力的DynamicAbilityTags  存在 InputTag时
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// 总是客户端调用。仅当在GameplayAbility上设置了bReplicateInputDirect时，才在服务器上调用。
			AbilitySpecInputPressed(AbilitySpec);
			// 如果未激活就激活能力
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}
// 抬起操作
void UAuraAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	// 遍历所有 可以被激活的能力
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// 当该能力的DynamicAbilityTags  存在 InputTag时
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// 总是客户端调用。仅当在GameplayAbility上设置了bReplicateInputDirect时，才在服务器上调用。
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	// 获得AssetTags
	GameplayEffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}


