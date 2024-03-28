// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/CarBase.h"

// Camera & SpringArm
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#if WITH_EDITOR
#include "Components/ArrowComponent.h"
#endif

#include "Utils/VehicleUnits.h"

// EnhancedInput
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

FName ACarBase::SpringArmComponentName(TEXT("SpringArm"));
FName ACarBase::CameraComponentName(TEXT("Camera"));

ACarBase::ACarBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCarMovementComponent>(AWheeledVehiclePawn::VehicleMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CarMovementComponent = CastChecked<UCarMovementComponent>(GetVehicleMovement());

#if WITH_EDITOR
	Arrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->ArrowColor = FColor::Yellow;
	Arrow->bTreatAsASprite = true;
	Arrow->SetupAttachment(GetMesh());
	Arrow->bLightAttachment = true;
	Arrow->bIsScreenSizeScaled = true;
#endif

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SpringArm = CreateOptionalDefaultSubobject<USpringArmComponent>(SpringArmComponentName);

	if (SpringArm)
	{
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bEnableCameraLag = true;
		SpringArm->TargetArmLength = 300.0f;

		SpringArm->SetupAttachment(GetMesh());

		Camera = CreateOptionalDefaultSubobject<UCameraComponent>(CameraComponentName);

		if (Camera)
		{
			Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void ACarBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputAsset->SteeringAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnSteering);
		EnhancedInputComponent->BindAction(InputAsset->SteeringAction, ETriggerEvent::Completed, this, &ACarBase::Input_OnSteering);

		EnhancedInputComponent->BindAction(InputAsset->ThrottleAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnThrottle);
		EnhancedInputComponent->BindAction(InputAsset->ThrottleAction, ETriggerEvent::Completed, this, &ACarBase::Input_OnThrottle);

		EnhancedInputComponent->BindAction(InputAsset->BrakeAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnBrake);
		EnhancedInputComponent->BindAction(InputAsset->BrakeAction, ETriggerEvent::Completed, this, &ACarBase::Input_OnBrake);

		EnhancedInputComponent->BindAction(InputAsset->ClutchAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnClutch);
		EnhancedInputComponent->BindAction(InputAsset->ClutchAction, ETriggerEvent::Completed, this, &ACarBase::Input_OnClutch);

		EnhancedInputComponent->BindAction(InputAsset->HandbrakeAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnHandbrake);
		EnhancedInputComponent->BindAction(InputAsset->HandbrakeAction, ETriggerEvent::Completed, this, &ACarBase::Input_OnHandbrake);

		EnhancedInputComponent->BindAction(InputAsset->ParkAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnPark);

		EnhancedInputComponent->BindAction(InputAsset->ShiftGearUpAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnGearShiftedUp);

		EnhancedInputComponent->BindAction(InputAsset->ShiftGearDownAction, ETriggerEvent::Triggered, this, &ACarBase::Input_OnGearShiftedDown);
	}
}

void ACarBase::NotifyControllerChanged()
{
	if (auto* PreviousPlayer = Cast<APlayerController>(PreviousController))
	{
		if (auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PreviousPlayer->GetLocalPlayer()))
		{
			InputSubsystem->RemoveMappingContext(InputMappingContext);
		}
	}

	if (auto* NewPlayer = Cast<APlayerController>(GetController()))
	{
		NewPlayer->InputYawScale_DEPRECATED = 1.0f;
		NewPlayer->InputPitchScale_DEPRECATED = 1.0f;
		NewPlayer->InputRollScale_DEPRECATED = 1.0f;

		if (auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayer->GetLocalPlayer()))
		{
			FModifyContextOptions Options;
			Options.bNotifyUserSettings = true;

			InputSubsystem->AddMappingContext(InputMappingContext, 0, Options);
		}
	}

	Super::NotifyControllerChanged();
}

void ACarBase::BeginPlay()
{
	Super::BeginPlay();

	bIsDriveable = true;
}

#pragma region Vehicle Interface
FVector ACarBase::GetAcceleration_Implementation() const
{
	return FVector::ZeroVector;

	// CarMovementComponent->GetAcceleration()
}

FVector ACarBase::GetVelocity_Implementation() const
{
	return FVector::ZeroVector;
	// CarMovementComponent->GetVelocity();
}

float ACarBase::GetSpeed_Implementation() const
{
	return 0.0f;  // CarMovementComponent->GetVelocity() | GetActorForwardVector();
}

float ACarBase::GetSpeedInKph_Implementation() const
{
	const float Speed = 0.0f;  // CarMovementComponent->GetVelocity() | GetActorForwardVector();
	return Speed * Nebulous::MeterPerSecondToKph;
}

float ACarBase::GetSpeedInMph_Implementation() const
{
	const float Speed = 0.0f;  // CarMovementComponent->GetVelocity() | GetActorForwardVector();
	return Speed * Nebulous::MeterPerSecondToMph;
}

bool ACarBase::IsDriveable_Implementation() const
{
	return bIsDriveable;
}

bool ACarBase::IsStopped_Implementation() const
{
	return false;
}

void ACarBase::SetDriveable_Implementation(bool bEnabled)
{
	if (bIsDriveable == bEnabled)
		return;

	OnDriveableChanged.Broadcast(bIsDriveable, bEnabled);

	bIsDriveable = bEnabled;
}
#pragma endregion

#pragma region Car Interface
bool ACarBase::IsOnAllWheels_Implementation() const
{
	return false;
}

float ACarBase::GetSteeringInput_Implementation() const
{
	return CarMovementComponent->GetSteeringInput();
}

float ACarBase::GetThrottleInput_Implementation() const
{
	return CarMovementComponent->GetThrottleInput();
}

float ACarBase::GetBrakeInput_Implementation() const
{
	return CarMovementComponent->GetBrakeInput();
}

float ACarBase::GetClutchInput_Implementation() const
{
	return CarMovementComponent->GetThrottleInput();
}

bool ACarBase::GetHandbrakeInput_Implementation() const
{
	return CarMovementComponent->GetHandbrakeInput();
}

bool ACarBase::IsParked_Implementation() const
{
	return CarMovementComponent->IsParked();
}

float ACarBase::GetEngineRPM_Implementation() const
{
	return 0.0f;
}

bool ACarBase::IsEngineRunning_Implementation() const
{
	return false;
}

void ACarBase::SetEngineEnabled_Implementation(bool bEnabled)
{
}

float ACarBase::GetClutchRatio_Implementation() const
{
	return 0.0f;
}

int32 ACarBase::GetGearIndex_Implementation() const
{
	return -1;
}

int32 ACarBase::GetNumOfGears_Implementation() const
{
	return -1;
}

void ACarBase::SetSteeringInput_Implementation(float AxisValue)
{
	CarMovementComponent->SetSteeringInput(AxisValue);
}

void ACarBase::SetThrottleInput_Implementation(float AxisValue)
{
	CarMovementComponent->SetThrottleInput(AxisValue);
}

void ACarBase::SetBrakeInput_Implementation(float AxisValue)
{
	CarMovementComponent->SetBrakeInput(AxisValue);
}

void ACarBase::SetClutchInput_Implementation(float AxisValue)
{
	CarMovementComponent->SetClutchInput(AxisValue);
}

void ACarBase::SetHandbrakeInput_Implementation(bool bNewValue)
{
	CarMovementComponent->SetHandbrakeInput(bNewValue);
}

void ACarBase::SetParkMode_Implementation(bool bNewValue)
{
	CarMovementComponent->SetParked(bNewValue);
}

void ACarBase::ShiftToGear_Implementation(int32 GearNum, bool bImmediate)
{
	CarMovementComponent->SetTargetGear(GearNum, bImmediate);
}
#pragma endregion

#pragma region Input Callbacks
void ACarBase::Input_OnSteering(const FInputActionValue& Value)
{
	SetSteeringInput(Value.Get<float>());
}

void ACarBase::Input_OnThrottle(const FInputActionValue& Value)
{
	SetThrottleInput(Value.Get<float>());
}

void ACarBase::Input_OnBrake(const FInputActionValue& Value)
{
	SetBrakeInput(Value.Get<float>());
}

void ACarBase::Input_OnClutch(const FInputActionValue& Value)
{
	SetClutchInput(Value.Get<float>());
}

void ACarBase::Input_OnHandbrake(const FInputActionValue& Value)
{
	constinit static float HANDBRAKE_THRESHOLD = 0.5f;
	SetHandbrakeInput(Value.Get<float>() >= HANDBRAKE_THRESHOLD);
}

void ACarBase::Input_OnPark(const FInputActionValue& Value)
{
	SetParkMode(!CarMovementComponent->IsParked());
}

void ACarBase::Input_OnGearShiftedUp(const FInputActionValue& Value)
{
	int32 GearNum = CarMovementComponent->GetTargetGear();
	GearNum++;
	ShiftToGear(GearNum, true);
}

void ACarBase::Input_OnGearShiftedDown(const FInputActionValue& Value)
{
	int32 GearNum = CarMovementComponent->GetTargetGear();
	GearNum--;
	ShiftToGear(GearNum, true);
}
#pragma endregion