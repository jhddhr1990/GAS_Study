// JHDDHR


#include "Controller/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraInputContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraInputContext,0);

	// 显示鼠标
	bShowMouseCursor = true;
	// 鼠标外观默认
	DefaultMouseCursor = EMouseCursor::Default;

	// 创建同时用于游戏模式和UI的输入设置
	FInputModeGameAndUI InputModeData;
	// 不锁定鼠标
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// 鼠标按下时捕获鼠标位置
	InputModeData.SetHideCursorDuringCapture(false);
	// 应用该设置
	SetInputMode(InputModeData);
}
