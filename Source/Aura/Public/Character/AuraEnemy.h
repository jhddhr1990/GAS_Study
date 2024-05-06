// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/CharacterInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

class AAuraAIController;
class UBehaviorTree;
struct FGameplayTag;
class UWidgetComponent;
// 属性委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyAttributeChangedSignature, float, NewAttribute);
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	// ~ IEnemyInterface 开始
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// ~ IEnemyInterface 结束

	virtual void InitAbilityActorInfo() override;
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnEnemyAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnEnemyAttributeChangedSignature OnMaxHealthChanged;

	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(BlueprintReadOnly, Category = "JHD")
	bool bHitReacting = false;
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCont);
	float BaseWalkSpeed = 250.f;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	int32 Level = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	virtual int32 GetPlayerLevel() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "JHD")
	TObjectPtr<UWidgetComponent> HealthBar;

	virtual void Die() override;

	UPROPERTY(EditAnywhere, Category = "JHD")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
