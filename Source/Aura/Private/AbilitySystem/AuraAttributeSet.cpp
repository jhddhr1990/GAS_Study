// JHDDHR


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraGASBlueprintFunctionLibrary.h"
#include "Interface/CombatInterface.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	TagsToAttributes.Add(AuraAttributes::Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Primary_Intellingence, GetIntelligenceAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Primary_Vigor, GetVigorAttribute);

	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);

	TagsToAttributes.Add(AuraAttributes::Attributes_Resistance_Fire, GetResistance_FireAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Resistance_Lightning, GetResistance_LightningAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Resistance_Arcane, GetResistance_ArcaneAttribute);
	TagsToAttributes.Add(AuraAttributes::Attributes_Resistance_Physical, GetResistance_PhysicalAttribute);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	/**
	* DOREPLIFETIME_CONDITION_NOTIFY用于声明属性在网络中复制，并在复制时触发通知。
	* (Class, Property, Condition, Notify)：这是宏的参数列表，包含了以下内容：
	* Class：需要复制属性的类名，通常是包含属性的 UObject 或其派生类。
	* Property：要复制的属性的名称，通常是一个 UPROPERTY。
	* Condition：复制属性的条件。它是一个枚举值，用于指定在何种情况下属性应该被复制到网络中。常见的条件包括：
	*		COND_None：不设置任何复制条件，属性总是被复制到网络中。
	*		COND_InitialOnly：属性只在初始复制时被复制到网络中，之后不再复制。
	*		COND_OwnerOnly：只有属性的所有者客户端会复制属性到网络中。
	*		COND_SkipOwner：属性的所有者客户端不会复制属性到网络中。
	*Notify：用于在属性复制时触发的通知函数的名称。这个函数应该是类中的一个成员函数，用于处理属性复制的通知。
	*在实际开发中，使用 REPNOTIFY_Always 可以确保当属性在网络中被复制时，无论属性的值是否有所改变，相关的通知函数都会被触发。
	*这样可以确保客户端和服务器端的属性状态保持同步，并在需要时执行相应的处理逻辑。
	*/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Fire, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Lightning, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Arcane, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Physical, COND_None, REPNOTIFY_Always);
}

// 在属性值被改变之前调用该函数
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	// NewValue：待改变的值。但是该值在这里clamp时，下次调用该函数的NewValue仍然时clamp之前的值
	// 例子：角色此时HP为98，吃下恢复药剂，会恢复10HP
	//		NewValue为待改变的HP值，此时数值为108，在这里clamp NewValue为100后，角色的Hp在修改后变为100。
	//		当角色再次吃下恢复药恢复HP时，NewValue的数值为118而不是110
	//      所以在这里clamp NewValue没用。
	
	// if (Attribute == GetHealthAttribute())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("PreNewValue %f"),NewValue)
	// 	//NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	// }
	// if (Attribute == GetManaAttribute())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("PreNewValue %f"),NewValue)
	// 	//NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	// }
}

// 该函数用来保存想要的GE信息
void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties)
{
	// GE的上下文
	Properties.EffectContextHandle = Data.EffectSpec.GetContext();
	// Source
	Properties.SourceASC = Properties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Properties.SourceASC) && Properties.SourceASC->AbilityActorInfo.IsValid() && Properties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		// Source AvatarActor
		Properties.SourceAvatarActor = Properties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		// Source Controller
		Properties.SourceController = Properties.SourceASC->AbilityActorInfo->PlayerController.Get();
		// Controller 可能为空，此步骤确保在AbilityActorInfo->PlayerController为空时，使用SourceAvatarActor获得Controller
		if (Properties.SourceController == nullptr && Properties.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Properties.SourceAvatarActor))
			{
				Properties.SourceController = Pawn->GetController();
			}
			if (Properties.SourceController)
			{
				Properties.SourceCharacter = Cast<ACharacter>(Properties.SourceController->GetPawn());
			}
		}
	}
	// Target
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetAvatarActor);
		Properties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetAvatarActor);
	}
}
// GE生效后调用，Data包含大量的GE信息，可以在此调试查看
void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// 创建想要在此保存GE信息的结构体
	FEffectProperties Props;
	// 调用自定义的保存该结构体的函数
	SetEffectProperties(Data, Props);
	// if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	// {
	// 	// 属性变化值
	// 	UE_LOG(LogTemp, Warning, TEXT("Post Magnitude %f"), Data.EvaluatedData.Magnitude);
	// }
	
	// clamp值
	if (GetMaxHealth() > 0.f) SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	if (GetMaxMana() > 0.f) SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			// 显示伤害数字
			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Data.Target.GetAvatarActor()))
			{
				CombatInterface->ShowDamageText(LocIncomingDamage, UAuraGASBlueprintFunctionLibrary::IsBlockedHit(Props.EffectContextHandle), UAuraGASBlueprintFunctionLibrary::IsCriticalHit(Props.EffectContextHandle));
			}
			// 对目标造成伤害时，角色激活对伤害做出反应的GA  
			if (NewHealth > 0.f)
			{
				FGameplayTagContainer GameplayTagContainer;
				GameplayTagContainer.AddTag(AuraEffects::Effects_HitReact);
				// 通过Tag 激活GA
				Data.Target.TryActivateAbilitiesByTag(GameplayTagContainer);
			}
			else
			{
				// 执行死亡
				if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Data.Target.GetAvatarActor()))
				{
					CombatInterface->Die();
				}
			}
		}
	}
	
	
}

// 当 Health 属性在网络中复制时，OnRep_Health 函数会被调用，同时传递旧的属性值作为参数。
// 在这个函数中，你可以根据需要执行任何与属性复制相关的操作，例如更新 UI、播放特效等。
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//GAMEPLAYATTRIBUTE_REPNOTIFY宏用于生成处理属性复制通知的代码.
	//它简化了在 Unreal Engine 中处理属性复制通知的过程，使你能够更轻松地编写网络同步的代码。
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_Resistance_Fire(const FGameplayAttributeData& OldResistance_Fire) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Fire, OldResistance_Fire);
}

void UAuraAttributeSet::OnRep_Resistance_Lightning(const FGameplayAttributeData& OldResistance_Lightning) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Lightning, OldResistance_Lightning);
}

void UAuraAttributeSet::OnRep_Resistance_Arcane(const FGameplayAttributeData& OldResistance_Arcane) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Arcane, OldResistance_Arcane);
}

void UAuraAttributeSet::OnRep_Resistance_Physical(const FGameplayAttributeData& OldResistance_Physical) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Physical, OldResistance_Physical);
}
