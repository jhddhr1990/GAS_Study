// JHDDHR


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
// ~ IAbilitySystemInterface 开始
UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
// ~ IAbilitySystemInterface 结束

void AAuraCharacterBase::InitAbilityActorInfo()
{
}



void AAuraCharacterBase::ApplyGEToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Lv) const
{
	check(GetAbilitySystemComponent());
	check(GameplayEffect);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, Lv, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyGEToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyGEToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyGEToSelf(InitializeAttributes, 1.f);
}
