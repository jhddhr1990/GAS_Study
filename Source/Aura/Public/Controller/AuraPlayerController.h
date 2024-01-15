// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

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
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category="JHD|Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;
	UPROPERTY(EditAnywhere, Category="JHD|Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& ActionValue);
};
