// JHDDHR


#include "Abilitys/AuraProjectileSpell.h"

#include "EffectActor/AuraProjectile.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UKismetSystemLibrary::PrintString(this, FString("111"), true, true, FLinearColor::Yellow);

	// 服务器检测，是否在服务器上运行s
	// const bool bIsServer = HasAuthority(&ActivationInfo);
	// if(!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SpawnLocation = CombatInterface->GetCombatSocketLocation();
		// TODO: 设置旋转
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnLocation);
		AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		// TODO: 给AuraProjectile一个GE来实现伤害
		AuraProjectile->FinishSpawning(SpawnTransform);
	}
	
	
	
}
