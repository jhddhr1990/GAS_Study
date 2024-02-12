// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

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
};
