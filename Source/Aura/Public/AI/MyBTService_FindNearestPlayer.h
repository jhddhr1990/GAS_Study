// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "MyBTService_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMyBTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD")
	FBlackboardKeySelector DistanceToTargetSelector;
};
