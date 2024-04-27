// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Abilitys/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
protected:
	// GE Class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "JHD")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "JHD")
	TMap<FGameplayTag, FScalableFloat> DamageType;
};
