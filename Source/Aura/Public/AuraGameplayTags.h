// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * 
 */
namespace AuraAttributes
{
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intellingence);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Resilience);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BlockChance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Mana);

	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Fire);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Lightning);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Arcane);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Physical);
}

namespace AuraInput
{
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LMB);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_RMB);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_1);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_2);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_3);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_4);
}

namespace AuraEvent
{
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_FireBolt);
}

namespace AuraMetaAttribute
{
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Meta_Damage);
}

namespace AuraEffects
{
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effects_HitReact);
}

namespace AuraDamageType
{
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Fire);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Lightning);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Arcane);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Physical);
}
