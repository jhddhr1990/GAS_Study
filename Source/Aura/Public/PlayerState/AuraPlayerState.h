// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	// ~ IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	FORCEINLINE int32 GetPlayerLevel() const { return Level;}
	
protected:
	// ~ AbilitySystem
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent>  AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	// ~
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JHD", ReplicatedUsing = "OnRep_Level")
	int32 Level = 1.f;
	UFUNCTION()
	void OnRep_Level();
	
};
