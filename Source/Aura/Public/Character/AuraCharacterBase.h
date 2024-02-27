// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"


class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
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

	// ~ AbilitySystem
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>  AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	// ~

	virtual void InitAbilityActorInfo();

	// 初始化默认属性的GE
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "JHD|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "JHD|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	// 初始属性
	void ApplyGEToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Lv) const;
	void InitializeDefaultAttributes() const;
};
