// JHDDHR


#include "AbilitySystem/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::GetAttributeInfoForTag(const FGameplayTag& AttributeTag, float bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AuraAttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("在%s中未找到%s"), *GetNameSafe(this), *AttributeTag.ToString());
	}
	return FAuraAttributeInfo();
}
