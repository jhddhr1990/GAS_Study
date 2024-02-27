// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

// 枚举EEffectApplicationPolicy，用于表示该Effect触发的条件
UENUM(Blueprintable)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

// 枚举EEffectRemovePolicy，用于表示该Effect是否主动移除
UENUM(Blueprintable)
enum class EEffectRemovePolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
protected:
	virtual void BeginPlay() override;

	// 该函数在蓝图中的BeginOverlap事件中调用
	UFUNCTION(BlueprintCallable, Category = "JHD")
	void OnOverlap(AActor* TargetActor);

	// 该函数在蓝图中的EndOverlap事件中调用
	UFUNCTION(BlueprintCallable, Category = "JHD")
	void OnEndOverlap(AActor* TargetActor);

	// 在Actor上应用指定的GE
	UFUNCTION(BlueprintCallable, Category = "JHD")
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	// 即时Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	EEffectApplicationPolicy InstanceEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// 有持续时间的Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;;

	// 无限持续时间的Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	EEffectRemovePolicy InfiniteEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverlap;// 该Effect必须主动移除

	// 创建FActiveGameplayEffectHandle为Key与UAbilitySystemComponent*为Value的键值对,
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	float ActorLevel = 1.f;
};