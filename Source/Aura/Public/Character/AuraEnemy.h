// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

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
	
	// ~ IEnemyInterface 开始
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// ~ IEnemyInterface 结束

	virtual void InitAbilityActorInfo() override;
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnEnemyAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="JHD|Attribute")
	FOnEnemyAttributeChangedSignature OnMaxHealthChanged;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	int32 Level = 1.f;
	virtual int32 GetPlayerLevel() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "JHD")
	TObjectPtr<UWidgetComponent> HealthBar;
};
