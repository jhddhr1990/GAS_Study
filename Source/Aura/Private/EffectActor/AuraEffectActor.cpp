// JHDDHR


#include "EffectActor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}
// 该函数在蓝图中的BeginOverlap事件中调用
void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag("Enemy") && !bIsEffectEnemy) return;
	
	if (InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

// 该函数在蓝图中的EndOverlap事件中调用
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag("Enemy") && !bIsEffectEnemy) return;
	
	if (InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		// 获得待取消对象的ASC
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		// 创建数组用于保存待移除的Effect
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		// 遍历ActiveEffectHandles键值对，当ASC相同时，取消该ASC的该Effect
		for (auto& HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)// 该值对应ASC
			{
				// RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle, int32 StacksToRemove)
				// StacksToRemove默认值为-1，清空堆栈Stacks。StacksToRemove > 0 为Stacks-1。
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		// 在键值对中删除已经取消的Effect效果
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Ue自带方法获得ASC组件 自带了各种检测
	UAbilitySystemComponent* ASCTarget = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if(ASCTarget == nullptr) return;
	// 检测是否设置了GE 
	check(GameplayEffectClass);

	// 创建游戏效果上下文句柄，该结构体FGameplayEffectContextHandle包含了执行游戏效果所需的相关信息
	FGameplayEffectContextHandle EffectContextHandle = ASCTarget->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);// 添加GE来源对象

	// 创建FGameplayEffectSpecHandle，允许蓝图生成一次 GameplayEffectSpec，然后通过句柄引用它，以便多次应用于多个目标。
	// MakeOutgoingSpec(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle Context)
	const FGameplayEffectSpecHandle EffectSpecHandle = ASCTarget->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

	// *EffectSpecHandle.Data.Get() 的解释:
	//       1. EffectSpecHandle是结构体FActiveGameplayEffectHandle，其中的对象Data的是TSharedPtr<FGameplayEffectSpec>。
	//       2. Data是共享指针，使用Get()方法获得该指针。
	// ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec &Spec, FPredictionKey PredictionKey):将FGameplayEffectSpec应用到ASC上
	//ASCTarget->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());直接应用效果

	// 将应用效果保存为FActiveGameplayEffectHandle,可以对生效的Effect进行管理。
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ASCTarget->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	// 判断该Effect的持续时间是否为Infinite
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// 添加到待取消的键值对中
	if(bIsInfinite && InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle, ASCTarget);
	}
	if (!bIsInfinite)
	{
		Destroy();
	}
}
