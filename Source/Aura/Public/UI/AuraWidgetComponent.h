// JHDDHR

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AuraWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "JHD")
	void SetDamageText(float Damage, bool IsBlocked, bool IsCritical);
};
