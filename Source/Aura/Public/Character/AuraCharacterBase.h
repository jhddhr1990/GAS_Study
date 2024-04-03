// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase();
	virtual void BeginPlay() override;
	
	// ~ IAbilitySystemInterface 开始
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~ IAbilitySystemInterface 结束
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponCombatSocketName;

	virtual FVector GetCombatSocketLocation() override;
	
	// ~ AbilitySystem
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>  AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	// ~

	// 用于初始化ASC的信息 和 Attribute信息
	virtual void InitAbilityActorInfo();

	// 初始化默认属性的GE
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "JHD|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "JHD|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "JHD|Attributes")
	TSubclassOf<UGameplayEffect> InitializeAttributes;
	
	// 初始属性
	void ApplyGEToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Lv) const;
	void InitializeDefaultAttributes() const;

	// 添加角色能力GA
	void AddCharacterAbilities();
private:
	// 角色拥有的能力GA数组列表
	UPROPERTY(EditAnywhere, Category = "JHD|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;
};
