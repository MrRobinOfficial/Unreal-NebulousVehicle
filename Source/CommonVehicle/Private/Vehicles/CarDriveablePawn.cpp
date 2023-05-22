// Copyright 2023 MrRobin. All Rights Reserved.

#include "Vehicles/CarDriveablePawn.h"
#include "Components/CommonVehicleMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"

ACarDriveablePawn::ACarDriveablePawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bEnableCameraLag = true;
    SpringArm->TargetArmLength = 300.0f;

    SpringArm->SetupAttachment(GetMesh());

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACarDriveablePawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (IsPlayerControlled())
    {
        if (auto* PlayerController = Cast<APlayerController>(GetController()))
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            {
                Subsystem->AddMappingContext(CarMappingContext, 0);
            }
        }
    }
}

void ACarDriveablePawn::UnPossessed()
{
    if (IsPlayerControlled())
    {
        if (auto* PlayerController = Cast<APlayerController>(GetController()))
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            {
                Subsystem->RemoveMappingContext(CarMappingContext);
            }
        }
    }

    Super::UnPossessed();
}

void ACarDriveablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnSteeringAction);
        EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ACarDriveablePawn::OnSteeringAction);

        EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnThrottleAction);
        EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ACarDriveablePawn::OnThrottleAction);

        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnBrakeAction);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ACarDriveablePawn::OnBrakeAction);

        EnhancedInputComponent->BindAction(ClutchAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnClutchAction);
        EnhancedInputComponent->BindAction(ClutchAction, ETriggerEvent::Completed, this, &ACarDriveablePawn::OnClutchAction);

        EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnHandbrakeAction);
        EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &ACarDriveablePawn::OnHandbrakeAction);

        EnhancedInputComponent->BindAction(ParkAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnParkAction);
        EnhancedInputComponent->BindAction(HonkAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnHonkAction);

        EnhancedInputComponent->BindAction(ShiftGearUpAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnGearShiftedUpAction);
        EnhancedInputComponent->BindAction(ShiftGearDownAction, ETriggerEvent::Triggered, this, &ACarDriveablePawn::OnGearShiftedDownAction);
    }
}

void ACarDriveablePawn::OnSteeringAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    CommonVehicleMovementComponent->SetSteeringInput(Value.Get<float>());
}

void ACarDriveablePawn::OnThrottleAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    CommonVehicleMovementComponent->SetThrottleInput(Value.Get<float>());
}

void ACarDriveablePawn::OnBrakeAction(const FInputActionValue& Value)
{
    CommonVehicleMovementComponent->SetBrakeInput(Value.Get<float>());
}

void ACarDriveablePawn::OnClutchAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    CommonVehicleMovementComponent->SetClutchInput(Value.Get<float>());
}

void ACarDriveablePawn::OnHandbrakeAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    CommonVehicleMovementComponent->SetHandbrakeInput(Value.Get<float>() >= 0.5f);
}

void ACarDriveablePawn::OnParkAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    bool bIsParked = CommonVehicleMovementComponent->IsParked();
    CommonVehicleMovementComponent->SetParked(!bIsParked);
}

void ACarDriveablePawn::OnHonkAction(const FInputActionValue& Value) { Honk(); }

void ACarDriveablePawn::OnGearShiftedUpAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    int32 GearNum = CommonVehicleMovementComponent->GetTargetGear();

    GearNum++;

    CommonVehicleMovementComponent->SetTargetGear(GearNum, true);
}

void ACarDriveablePawn::OnGearShiftedDownAction(const FInputActionValue& Value)
{
    if (!IsValid(CommonVehicleMovementComponent))
        return;

    int32 GearNum = CommonVehicleMovementComponent->GetTargetGear();

    GearNum--;

    CommonVehicleMovementComponent->SetTargetGear(GearNum, true);
}