// JHDDHR


#include "PlayerState/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	// ~ AbilitySystem
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	AbilitySystemComponent->SetIsReplicated(true);// 设置AbilitySystemComponent可复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);// 设置AbilitySystemComponent复制模式
	
	NetUpdateFrequency = 100.f;// 网络同步更新的频率 这里是设置调高到100
}
// ~ IAbilitySystemInterface
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
//~~~~~~~~~~~~~~~~~~~~~~