// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "Interface/EnemyInterface.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category="JHD|Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;
	UPROPERTY(EditAnywhere, Category="JHD|Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category="JHD|Input")
	TObjectPtr<UInputAction> LookAction;

	void Move(const FInputActionValue& ActionValue);
	void Look(const FInputActionValue& ActionValue);

	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	// 接收输入参数绑定的函数
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	void AbilityInputHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category = "JHD|Input")
	TObjectPtr<UAuraInputConfig> AuraInputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();
};
