// JHDDHR


#include "Abilitys/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EffectActor/AuraProjectile.h"
#include "Interface/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UKismetSystemLibrary::PrintString(this, FString("111"), true, true, FLinearColor::Yellow);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	// 服务器检测，是否在服务器上运行s
	// const bool bIsServer = HasAuthority(&ActivationInfo);
	// if(!bIsServer) return;
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SpawnLocation = CombatInterface->GetCombatSocketLocation();
		// TODO: 设置旋转
		FRotator Rotation = (TargetLocation - SpawnLocation).Rotation();
		Rotation.Pitch = 0.f;
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		// TODO: 给AuraProjectile一个GE来实现伤害
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectContextHandle GameplayEffectContextHandle = SourceASC->MakeEffectContext();
		// GameplayEffectContextHandle包含了大量信息
		GameplayEffectContextHandle.SetAbility(this);
		GameplayEffectContextHandle.AddSourceObject(AuraProjectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(AuraProjectile);
		GameplayEffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = SpawnLocation;
		GameplayEffectContextHandle.AddHitResult(HitResult);
		
		const FGameplayEffectSpecHandle GESpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), GameplayEffectContextHandle);

		for (auto& Damage: DamageType)
		{
			const float ScaledDamage = Damage.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(GESpecHandle, Damage.Key, ScaledDamage);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("DamageType %s : Damage %f"),*Damage.Key.GetTagName().ToString(), ScaledDamage));
		}
		//UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(GESpecHandle, AuraMetaAttribute::Attributes_Meta_Damage, ScaledDamage);
		
		AuraProjectile->DamageEffectSpecHandle = GESpecHandle;
		AuraProjectile->FinishSpawning(SpawnTransform);
	}
}
