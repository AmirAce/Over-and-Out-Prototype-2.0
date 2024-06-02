// 1011Blueprints.


#include "OnO_MainCharacter.h"
#include "AlsCameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ALSCamera/Public/AlsCameraComponent.h"
//#include "ALSExtras/Public/AlsCharacterExample.h"
#include "DatasmithDefinitions.h"
#include "DatasmithFacadeActor.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerController.h"
#include "AlsAnimationInstance.h"
#include "AlsCharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/GameNetworkManager.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"
#include "Settings/AlsCharacterSettings.h"
#include "Utility/AlsConstants.h"
#include "Utility/AlsMacros.h"
#include "Utility/AlsUtility.h"
#include "AlsCharacter.h"

  AOnO_MainCharacter ::AOnO_MainCharacter()
{
	Camera = CreateDefaultSubobject<UAlsCameraComponent>(FName{TEXTVIEW("Camera")});
	Camera->SetupAttachment(GetMesh());
	Camera->SetRelativeRotation_Direct({0.0f, 90.0f, 0.0f});
  	
}
void AOnO_MainCharacter::NotifyControllerChanged()
{
  	const auto* PreviousPlayer{Cast<APlayerController>(PreviousController)};
  	if (IsValid(PreviousPlayer))
  	{
  		auto* InputSubsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PreviousPlayer->GetLocalPlayer())};
  		if (IsValid(InputSubsystem))
  		{
  			InputSubsystem->RemoveMappingContext(InputMappingContext);
  		}
  	}

  	auto* NewPlayer{Cast<APlayerController>(GetController())};
  	if (IsValid(NewPlayer))
  	{
  		NewPlayer->InputYawScale_DEPRECATED = 1.0f;
  		NewPlayer->InputPitchScale_DEPRECATED = 1.0f;
  		NewPlayer->InputRollScale_DEPRECATED = 1.0f;

  		auto* InputSubsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayer->GetLocalPlayer())};
  		if (IsValid(InputSubsystem))
  		{
  			FModifyContextOptions Options;
  			Options.bNotifyUserSettings = true;

  			InputSubsystem->AddMappingContext(InputMappingContext, 0, Options);
  		}
  	}

  	Super::NotifyControllerChanged();
}
//void AONO_MainCharacter::



void AOnO_MainCharacter::CalcCamera(const float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	if (Camera->IsActive())
	{
		Camera->GetViewInfo(ViewInfo);
		return;
	}

	Super::CalcCamera(DeltaTime, ViewInfo);
}

void AOnO_MainCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	auto* EnhancedInput{Cast<UEnhancedInputComponent>(Input)};
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLookMouse);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLook);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnMove);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSprint);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnWalk);
		EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnCrouch);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnJump);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnAim);
		EnhancedInput->BindAction(RagdollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRagdoll);
		EnhancedInput->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRoll);
		EnhancedInput->BindAction(RotationModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRotationMode);
		EnhancedInput->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnAssassination
			);
		// EnhancedInput->BindAction(SwitchShoulderAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchShoulder);
		// EnhancedInput->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnShoot);
	}
}

void AOnO_MainCharacter::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	const auto Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpMouseSensitivity);
	AddControllerYawInput(Value.X * LookRightMouseSensitivity);
}

void AOnO_MainCharacter::Input_OnLook(const FInputActionValue& ActionValue)
{
	const auto Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpRate);
	AddControllerYawInput(Value.X * LookRightRate);
}

void AOnO_MainCharacter::Input_OnMove(const FInputActionValue& ActionValue)
{
	const auto Value{UAlsMath::ClampMagnitude012D(ActionValue.Get<FVector2D>())};

	const auto ForwardDirection{UAlsMath::AngleToDirectionXY(UE_REAL_TO_FLOAT(GetViewState().Rotation.Yaw))};
	const auto RightDirection{UAlsMath::PerpendicularCounterClockwiseXY(ForwardDirection)};

	AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void AOnO_MainCharacter::Input_OnSprint(const FInputActionValue& ActionValue)
{
	SetDesiredGait(ActionValue.Get<bool>() ? AlsGaitTags::Sprinting : AlsGaitTags::Running);
}

void AOnO_MainCharacter::Input_OnWalk()
{
	if (GetDesiredGait() == AlsGaitTags::Walking)
	{
		SetDesiredGait(AlsGaitTags::Running);
	}
	else if (GetDesiredGait() == AlsGaitTags::Running)
	{
		SetDesiredGait(AlsGaitTags::Walking);
	}
}

void AOnO_MainCharacter::Input_OnCrouch()
{
	if (GetDesiredStance() == AlsStanceTags::Standing)
	{
		SetDesiredStance(AlsStanceTags::Crouching);
	}
	else if (GetDesiredStance() == AlsStanceTags::Crouching)
	{
		SetDesiredStance(AlsStanceTags::Standing);
	}
}

void AOnO_MainCharacter::Input_OnJump(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (StopRagdolling())
		{
			return;
		}

		if (StartMantlingGrounded())
		{
			return;
		}

		if (GetStance() == AlsStanceTags::Crouching)
		{
			SetDesiredStance(AlsStanceTags::Standing);
			return;
		}

		Jump();
	}
	else
	{
		StopJumping();
	}
}

void AOnO_MainCharacter::Input_OnAim(const FInputActionValue& ActionValue)
{
	SetDesiredAiming(ActionValue.Get<bool>());
}

void AOnO_MainCharacter::Input_OnRagdoll()
{
	if (!StopRagdolling())
	{
		StartRagdolling();
	}
}

void AOnO_MainCharacter::Input_OnRoll()
{
	static constexpr auto PlayRate{1.3f};

	StartRolling(PlayRate);
}

void AOnO_MainCharacter::Input_OnRotationMode()
{
	SetDesiredRotationMode(GetDesiredRotationMode() == AlsRotationModeTags::VelocityDirection
		                       ? AlsRotationModeTags::ViewDirection
		                       : AlsRotationModeTags::VelocityDirection);
}

void AOnO_MainCharacter::Input_OnAssassination()
{
	//SetViewMode(GetViewMode() == AlsViewModeTags::ThirdPerson ? AlsViewModeTags::FirstPerson : AlsViewModeTags::ThirdPerson);
}

UAlsMantlingSettings* AOnO_MainCharacter::SelectMantlingSettings(EAlsMantlingType MantlingType)
{
  	return Super::SelectMantlingSettings_Implementation(MantlingType);
}



// ReSharper disable once CppMemberFunctionMayBeConst
//void AOnO_MainCharacter::Input_OnSwitchShoulder()
//{
//	Camera->SetRightShoulder(!Camera->IsRightShoulder());
//}

void AOnO_MainCharacter::Input_OnShoot()
  {
		  
  }

//
// void AOnO_MainCharacter::SetOverlayMode(const FGameplayTag& NewOverlayMode, const bool bSendRpc)
//   {
//   	if (OverlayMode == NewOverlayMode || GetLocalRole() <= ROLE_SimulatedProxy)
//   	{
//   		return;
//   	}

  // 	const auto PreviousOverlayMode{OverlayMode};
  //
  // 	OverlayMode = NewOverlayMode;
  //
  // 	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, OverlayMode, this)
  //
	 //  OnOverlayModeChanged(PreviousOverlayMode);
  //
  // 	if (bSendRpc)
  // 	{
  // 		if (GetLocalRole() >= ROLE_Authority)
  // 		{
  // 			// ClientSetOverlayMode(OverlayMode);
  // 		}
  // 		else
  // 		{
  // 			// ServerSetOverlayMode(OverlayMode);
  // 		}
  // 	}
  // }
//
// void AOnO_MainCharacter::OnReplicated_OverlayMode(const FGameplayTag& PreviousOverlayMode)
//   {
//   	OnOverlayModeChanged(PreviousOverlayMode);
//   }
//void AAlsCharacter::OnOverlayModeChanged_Implementation(const FGameplayTag& PreviousOverlayMode) {}



void AOnO_MainCharacter::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& Unused, float& VerticalLocation)
{
	if (Camera->IsActive())
	{
		Camera->DisplayDebug(Canvas, DisplayInfo, VerticalLocation);
	}

	Super::DisplayDebug(Canvas, DisplayInfo, Unused, VerticalLocation);
}
void AOnO_MainCharacter::BeginPlay()
  {
  	ALS_ENSURE(IsValid(Settings));
  	ALS_ENSURE(IsValid(MovementSettings));
  	ALS_ENSURE(AnimationInstance.IsValid());

  	ALS_ENSURE_MESSAGE(!bUseControllerRotationPitch && !bUseControllerRotationYaw && !bUseControllerRotationRoll,
						 TEXT("These settings are not allowed and must be turned off!"));

  	Super::BeginPlay();

  	if (GetLocalRole() >= ROLE_AutonomousProxy)
  	{
  		// Teleportation of simulated proxies is detected differently, see
  		// AAlsCharacter::PostNetReceiveLocationAndRotation() and AAlsCharacter::OnRep_ReplicatedBasedMovement().

  		GetCapsuleComponent()->TransformUpdated.AddWeakLambda(
			  this, [this](USceneComponent*, const EUpdateTransformFlags, const ETeleportType TeleportType)
			  {
				  if (TeleportType != ETeleportType::None && AnimationInstance.IsValid())
				  {
					  AnimationInstance->MarkTeleported();
				  }
			  });
  	}

//  	RefreshMeshProperties();

  	ViewState.NetworkSmoothing.bEnabled |= IsValid(Settings) &&
		  Settings->View.bEnableNetworkSmoothing && GetLocalRole() == ROLE_SimulatedProxy;

  	// Update states to use the initial desired values.

  	RefreshRotationMode();

  	AlsCharacterMovement->SetRotationMode(RotationMode);

  	ApplyDesiredStance();

  	AlsCharacterMovement->SetStance(Stance);

  	//RefreshGait();

  	OnOverlayModeChanged(OverlayMode);
  }
