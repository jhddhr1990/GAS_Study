// JHDDHR


#include "UI/AuraHUD.h"
#include "UI/AuraUserWidget.h"


void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),MainWidgetClass);
	Widget->AddToViewport();
}
