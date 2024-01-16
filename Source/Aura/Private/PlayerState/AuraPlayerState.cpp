// JHDDHR


#include "PlayerState/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	// ~ AbilitySystem
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AbilitySystemComponent->SetOwnerActor(this);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	NetUpdateFrequency = 100.f;
}
// ~ IAbilitySystemInterface
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
//~~~~~~~~~~~~~~~~~~~~~~