// JHDDHR


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "UI/AuraWidgetComponent.h"

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

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponCombatSocketName);
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}


// 将GE应用自身
void AAuraCharacterBase::ApplyGEToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Lv) const
{
	check(GetAbilitySystemComponent());
	check(GameplayEffect);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, Lv, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
// 初始化人物属性值
void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyGEToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyGEToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyGEToSelf(InitializeAttributes, 1.f);
}

// 添加角色能力GA
void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	// if (!HasAuthority()) return; 网络游戏使用
	// 调用ASC上的自定义函数AddCharacterAbilities，在ASC上完成能力GA的添加
	AuraASC->AddCharacterAbilities(StartUpAbilities);
}

void AAuraCharacterBase::ShowDamageText(float Damage, bool IsBlocked, bool IsCritical)
{
	if (IsValid(FloatDamageComponent))
	{
		UAuraWidgetComponent* AuraWidgetComponent = NewObject<UAuraWidgetComponent>(this, FloatDamageComponent);
		AuraWidgetComponent->RegisterComponent();
		AuraWidgetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		AuraWidgetComponent->SetDamageText(Damage, IsBlocked, IsCritical);
		AuraWidgetComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}
