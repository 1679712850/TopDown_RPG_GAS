// Copyright 13


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Actor/MagicCircle.h"
#include "Components/DecalComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "TopDown_RPG_GAS/TopDown_RPG_GAS.h"
#include "UI/DamageTextComponent.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (auto ControlledPawn = GetPawn())
	{
		const auto LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const auto Direction = Spline->FindDirectionClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
	UpdateMagicCircleLocation();
}

void AAuraPlayerController::ShowMagicCircle(UMaterialInterface* DecalMaterial)
{
	if (!IsValid(MagicCircle))
	{
		MagicCircle = GetWorld()->SpawnActor<AMagicCircle>(MagicCircleClass);
		if (DecalMaterial)
		{
			MagicCircle->MagicCircleDecal->SetMaterial(0, DecalMaterial);
		}
	}
}

void AAuraPlayerController::HideMagicCircle()
{
	if (IsValid(MagicCircle))
	{
		MagicCircle->Destroy();
	}
}

void AAuraPlayerController::UpdateMagicCircleLocation()
{
	if (IsValid(MagicCircle))
	{
		MagicCircle->SetActorLocation(CursorHit.ImpactPoint);
	}
}

void AAuraPlayerController::CursorTrace()
{
	if (GetAuraAbilitySystemComponent() && GetAuraAbilitySystemComponent()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_CursorTrace))
	{
		if (LastActor) LastActor->UnHighlight();
		if (ThisActor) ThisActor->UnHighlight();
		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}
	const ECollisionChannel TraceChannel = IsValid(MagicCircle) ? ECC_ExcludePlayers : ECC_Visibility;
	GetHitResultUnderCursor(TraceChannel, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IHighlightInterface>(CursorHit.GetActor());

	/*
	 * Line trace from cursor. There are several scenarios:
	 * A. LastActor is NULL && ThisActor is NULL
	 *		- Do nothing
	 * B. LastActor is NULL && ThisActor is Valid
	 * 		- Highlight ThisActor
	 * C. LastActor is Valid && ThisActor is NULL
	 * 		- Unhighlight LastActor
	 * D. Both are valid, but LastActor != ThisActor
	 * 		- Unhighlight LastActor, and Highlight ThisActor
	 * E. Both are valid, but LastActor == ThisActor
	 * 		- Do nothing
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->Highlight();
		}
		else
		{
			// Case A, do nothing
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlight();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlight();
				ThisActor->Highlight();
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
	if (GetAuraAbilitySystemComponent() && GetAuraAbilitySystemComponent()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
	if (GetAuraAbilitySystemComponent()) GetAuraAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
}

void AAuraPlayerController::AbilityTagInputReleased(FGameplayTag InputTag)
{
	
	if (GetAuraAbilitySystemComponent() && GetAuraAbilitySystemComponent()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (auto AuraASC = GetAuraAbilitySystemComponent())
		{
			AuraASC->OnAbilityTagInputReleased(InputTag);
		}
		return;
	}

	if (GetAuraAbilitySystemComponent())
	{
		GetAuraAbilitySystemComponent()->OnAbilityTagInputReleased(InputTag);
	}

	if (!bTargeting && !bShiftKeyDown)
	{
		auto ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (auto NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const auto& Point : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), Point, 8.f, 8, FColor::Green, false, 5.f);
				}
				bAutoRunning = true;
				if (!NavPath->PathPoints.IsEmpty())
				{
					CachedDestination = NavPath->PathPoints.Last();
				}
			}
		}
		if (GetAuraAbilitySystemComponent() && !GetAuraAbilitySystemComponent()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ClickNiagaraSystem, CachedDestination);
		}
		FollowTime = 0.f;
	}
}

void AAuraPlayerController::AbilityTagInputHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (auto AuraASC = GetAuraAbilitySystemComponent())
		{
			AuraASC->OnAbilityTagInputHeld(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (auto AuraASC = GetAuraAbilitySystemComponent())
		{
			AuraASC->OnAbilityTagInputHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
		
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
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

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto EnhancedInputComponent = Cast<UAuraEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::OnMove);
	EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
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
