// JHDDHR


#include "AuraGameplayTags.h"

namespace AuraAttributes
{
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Intellingence, FName{TEXTVIEW("Attributes.Primary.Intellingence")});
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Resilience, FName{TEXTVIEW("Attributes.Primary.Resilience")});
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Strength, FName{TEXTVIEW("Attributes.Primary.Strength")});
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Vigor, FName{TEXTVIEW("Attributes.Primary.Vigor")});
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxHealth, FName{TEXTVIEW("Attributes.Secondary.MaxHealth")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxMana, FName{TEXTVIEW("Attributes.Secondary.MaxMana")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_Armor, FName{TEXTVIEW("Attributes.Secondary.Armor")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ArmorPenetration, FName{TEXTVIEW("Attributes.Secondary.ArmorPenetration")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_BlockChance, FName{TEXTVIEW("Attributes.Secondary.BlockChance")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitChance, FName{TEXTVIEW("Attributes.Secondary.CriticalHitChance")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitDamage, FName{TEXTVIEW("Attributes.Secondary.CriticalHitDamage")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitResistance, FName{TEXTVIEW("Attributes.Secondary.CriticalHitResistance")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_HealthRegeneration, FName{TEXTVIEW("Attributes.Secondary.HealthRegeneration")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ManaRegeneration, FName{TEXTVIEW("Attributes.Secondary.ManaRegeneration")})
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Health, FName{TEXTVIEW("Attributes.Vital.Health")});
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Mana, FName{TEXTVIEW("Attributes.Vital.Mana")});
}

namespace AuraInput
{
	UE_DEFINE_GAMEPLAY_TAG(Input_LMB, FName{TEXTVIEW("Input.LMB")});
	UE_DEFINE_GAMEPLAY_TAG(Input_RMB, FName{TEXTVIEW("Input.RMB")});
	UE_DEFINE_GAMEPLAY_TAG(Input_1, FName{TEXTVIEW("Input.1")});
	UE_DEFINE_GAMEPLAY_TAG(Input_2, FName{TEXTVIEW("Input.2")});
	UE_DEFINE_GAMEPLAY_TAG(Input_3, FName{TEXTVIEW("Input.3")});
	UE_DEFINE_GAMEPLAY_TAG(Input_4, FName{TEXTVIEW("Input.4")});
}

namespace AuraEvent
{
	UE_DEFINE_GAMEPLAY_TAG(Montage_FireBolt, FName{TEXTVIEW("Event.Montage.FireBolt")});
}

namespace AuraMetaAttribute
{
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Meta_Damage, FName{TEXTVIEW("Attributes.Meta.Damage")});
}

namespace AuraEffects
{
	UE_DEFINE_GAMEPLAY_TAG(Effects_HitReact, FName{TEXTVIEW("Effects.HitReact")});
}