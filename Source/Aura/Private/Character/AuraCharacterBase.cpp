// JHDDHR


#include "Character/AuraCharacterBase.h"

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