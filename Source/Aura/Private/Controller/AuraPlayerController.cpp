// JHDDHR


#include "Controller/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraEnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.bBlockingHit) {return;}
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	if (LastActor == nullptr && ThisActor != nullptr)
	{
		ThisActor->HighlightActor();
	}
	if (LastActor != nullptr && ThisActor != nullptr)
	{
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();
	}
	if(LastActor != nullptr && ThisActor == nullptr)
	{
		LastActor->UnHighlightActor();
	}
}

void AAuraPlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Black, *InputTag.ToString());
}

void AAuraPlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputReleased(InputTag);
}

void AAuraPlayerController::AbilityInputHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Cyan, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		return Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraInputContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraInputContext,0);
	}

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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// 类型转换为自定义的增强输入
	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	check(AuraEnhancedInputComponent);
	// 用默认的绑定操作
	AuraEnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	AuraEnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Look);
	check(AuraInputConfig);
	// 用自定义的绑定操作
	AuraEnhancedInputComponent->BindAbilityActions(AuraInputConfig, this, &AAuraPlayerController::AbilityInputPressed,
		&AAuraPlayerController::AbilityInputPressed, &AAuraPlayerController::AbilityInputHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& ActionValue)
{
	const FVector2d InputAxisVector = ActionValue.Get<FVector2d>();
	const FRotator YawRotation(0,GetControlRotation().Yaw,0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AAuraPlayerController::Look(const FInputActionValue& ActionValue)
{
	const float YawInput = ActionValue.Get<FVector2d>().X;
	AddYawInput(YawInput);
}


