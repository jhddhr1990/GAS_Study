// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterInfo.generated.h"


class UGameplayEffect;

// 枚举 怪物类别
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

// 结构体 初始属性信息
USTRUCT(BlueprintType)
struct FCharacterDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = "JHD")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

/**
 * 
 */
UCLASS()
class AURA_API UCharacterInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	// 键值对 怪物类别 对应 属性信息
	UPROPERTY(EditDefaultsOnly, Category = "JHD")
	TMap<ECharacterClass, FCharacterDefaultInfo> CharacterInformation;

	// 通用属性信息
	UPROPERTY(EditDefaultsOnly, Category = "JHD|Common")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	// 通用属性信息
	UPROPERTY(EditDefaultsOnly, Category = "JHD|Common")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	// 通过怪物类别查找属性信息
	FCharacterDefaultInfo GetFCharacterDefaultInfo(ECharacterClass CharacterClass);
};
