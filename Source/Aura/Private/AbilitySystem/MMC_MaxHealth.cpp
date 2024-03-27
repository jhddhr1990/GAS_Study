// JHDDHR


#include "AbilitySystem/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// 捕获的属性是Vigor
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	// 数据源是GE的Target
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
	// 将该捕获的属性添加到计算中
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	// 将要捕获的属性值赋予到创建的变量中
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	// 限定一下最大最小值
	Vigor = FMath::Max<float>(Vigor, 0.f);

	// 通过接口获得等级
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	// 返回最终计算的值
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
