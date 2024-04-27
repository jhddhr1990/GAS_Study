// JHDDHR


#include "AbilitySystem/EC_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraGASBlueprintFunctionLibrary.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor); // 护甲
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);// 护甲穿透
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);// 格挡率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);// 暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);// 暴击伤害
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);// 暴击抗性

	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire);// 火抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Lightning);// 雷抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Arcane);// 法抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Physical);// 物理抗性

	// TMap<FGameplayTag, const FGameplayEffectAttributeCaptureDefinition> DamageResistance;
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Fire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Lightning, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Arcane, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Physical, Target, false);

		// DamageResistance.Add(AuraDamageType::Damage_Fire, Resistance_FireDef);
		// DamageResistance.Add(AuraDamageType::Damage_Lightning, Resistance_LightningDef);
		// DamageResistance.Add(AuraDamageType::Damage_Arcane, Resistance_ArcaneDef);
		// DamageResistance.Add(AuraDamageType::Damage_Physical, Resistance_PhysicalDef);
	}
};
static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}
UEC_Damage::UEC_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);

	RelevantAttributesToCapture.Add(DamageStatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_LightningDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ArcaneDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_PhysicalDef);

	// 键值对 对应 属性伤害值Tag和属性抵抗值Tag
	DamageTypesToResistances.Add(AuraDamageType::Damage_Fire, AuraAttributes::Attributes_Resistance_Fire);
	DamageTypesToResistances.Add(AuraDamageType::Damage_Lightning, AuraAttributes::Attributes_Resistance_Lightning);
	DamageTypesToResistances.Add(AuraDamageType::Damage_Arcane, AuraAttributes::Attributes_Resistance_Arcane);
	DamageTypesToResistances.Add(AuraDamageType::Damage_Physical, AuraAttributes::Attributes_Resistance_Physical);

	// 键值对 对应 属性伤害值Tag和属性抵抗捕获值
	DamageResistance.Add(AuraDamageType::Damage_Fire, DamageStatics().Resistance_FireDef);
	DamageResistance.Add(AuraDamageType::Damage_Lightning, DamageStatics().Resistance_LightningDef);
	DamageResistance.Add(AuraDamageType::Damage_Arcane, DamageStatics().Resistance_ArcaneDef);
	DamageResistance.Add(AuraDamageType::Damage_Physical, DamageStatics().Resistance_PhysicalDef);
}

void UEC_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// 为计算做准备
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	// 伤害值通过Tag获取
	// 遍历伤害的各个属性伤害值叠加出最终的伤害值
	float Damage = 0.f;
	for (auto& DamageTypeTag : DamageTypesToResistances)
	{
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag.Key, false);
		// 当只有存在属性伤害值的时候 捕获出属性抵抗值来进行属性抵抗
		if (DamageTypeValue > 0.f)
		{
			float DamageTypeResistance = 0.f;
			const FGameplayEffectAttributeCaptureDefinition CaptureDefinition = DamageResistance[DamageTypeTag.Key];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDefinition, EvaluateParameters, DamageTypeResistance);
			DamageTypeValue -= DamageTypeResistance;
		}
		Damage += DamageTypeValue;
	}
	
	//格挡参与计算
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance);
	const bool bBlocked = FMath::RandRange(1.f, 100.f) < (TargetBlockChance * 100.f);
	UAuraGASBlueprintFunctionLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	Damage = bBlocked ? Damage / 2.f : Damage;
	//护甲、护甲穿透参与计算
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);

	const float EffectArmor = TargetArmor * ((100 - SourceArmorPenetration) / 100.f );
	Damage = Damage * (EffectArmor / TargetArmor);
	//暴击率、暴击抗性、暴击伤害参与计算
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluateParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(0.f, SourceCriticalHitChance);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(0.f, SourceCriticalHitDamage);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(0.f, TargetCriticalHitResistance);

	const float CriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance > 0.f ? SourceCriticalHitChance - TargetCriticalHitResistance : 0.f;
	const bool bIsCriticalHit = FMath::RandRange(1.f, 100.f) < (CriticalHitChance);
	UAuraGASBlueprintFunctionLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);
	if (bIsCriticalHit)
	{
		Damage = Damage * SourceCriticalHitDamage;
	}
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
