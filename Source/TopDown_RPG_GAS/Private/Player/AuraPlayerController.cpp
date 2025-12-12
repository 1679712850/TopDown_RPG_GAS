// Copyright 13


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


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
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastEnemy = CurrentEnemy;
	CurrentEnemy = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
	 * Line trace from cursor. There are several scenarios:
	 * A. LastEnemy is NULL && CurrentEnemy is NULL
	 *		- Do nothing
	 * B. LastEnemy is NULL && CurrentEnemy is Valid
	 * 		- Highlight CurrentEnemy
	 * C. LastEnemy is Valid && CurrentEnemy is NULL
	 * 		- Unhighlight LastEnemy
	 * D. Both are valid, but LastEnemy != CurrentEnemy
	 * 		- Unhighlight LastEnemy, and Highlight CurrentEnemy
	 * E. Both are valid, but LastEnemy == CurrentEnemy
	 * 		- Do nothing
	 */
	if (LastEnemy == nullptr)
	{
		if (CurrentEnemy != nullptr)
		{
			// Case B
			CurrentEnemy->Highlight();
		}
		else
		{
			// Case A, do nothing
		}
	}
	else
	{
		if (CurrentEnemy == nullptr)
		{
			// Case C
			LastEnemy->UnHighlight();
		}
		else
		{
			if (LastEnemy != CurrentEnemy)
			{
				// Case D
				LastEnemy->UnHighlight();
				CurrentEnemy->Highlight();
			}
			else
			{
				// Case E, do nothing
			}
		}
	}
}

void AAuraPlayerController::AbilityTagInputPressed(FGameplayTag InputTag)
{
}

void AAuraPlayerController::AbilityTagInputReleased(FGameplayTag InputTag)
{
	if (auto AuraASC = GetAuraAbilitySystemComponent())
	{
		AuraASC->OnAbilityTagInputReleased(InputTag);
	}
}

void AAuraPlayerController::AbilityTagInputHeld(FGameplayTag InputTag)
{
	if (auto AuraASC = GetAuraAbilitySystemComponent())
	{
		AuraASC->OnAbilityTagInputHeld(InputTag);
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraMappingContext);

	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraMappingContext, 0 );
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto EnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::OnMove);
	EnhancedInputComponent->BindAbilityActions(InputConfig, this, 
		&AAuraPlayerController::AbilityTagInputPressed,
		&AAuraPlayerController::AbilityTagInputReleased,
		&AAuraPlayerController::AbilityTagInputHeld);
}

void AAuraPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (auto ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}
