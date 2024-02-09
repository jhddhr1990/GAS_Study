// JHDDHR


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
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
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties)
{
	Properties.EffectContextHandle = Data.EffectSpec.GetContext();
	Properties.SourceASC = Properties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Properties.SourceASC) && Properties.SourceASC->AbilityActorInfo.IsValid() && Properties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.SourceAvatarActor = Properties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Properties.SourceController = Properties.SourceASC->AbilityActorInfo->PlayerController.Get();
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
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetAvatarActor);
		Properties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetAvatarActor);
	}
}
void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%f"), GetHealth());
	// 	UE_LOG(LogTemp, Warning, TEXT("%f"), Data.EvaluatedData.Magnitude);
	// }
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
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