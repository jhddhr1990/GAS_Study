// JHDDHR


#include "AbilitySystem/CharacterInfo.h"

FCharacterDefaultInfo UCharacterInfo::GetFCharacterDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterInformation.FindChecked(CharacterClass);
}
