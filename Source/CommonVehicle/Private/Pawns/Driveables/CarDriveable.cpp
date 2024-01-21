// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/Driveables/CarDriveable.h"
#include "Components/CommonVehicleMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// %% EnhancedInput Module %%
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACarDriveable::ACarDriveable(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
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

void ACarDriveable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(InputAsset->SteeringAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnSteering);
        EnhancedInputComponent->BindAction(InputAsset->SteeringAction, ETriggerEvent::Completed, this, &ACarDriveable::Input_OnSteering);

        EnhancedInputComponent->BindAction(InputAsset->ThrottleAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnThrottle);
        EnhancedInputComponent->BindAction(InputAsset->ThrottleAction, ETriggerEvent::Completed, this, &ACarDriveable::Input_OnThrottle);

        EnhancedInputComponent->BindAction(InputAsset->BrakeAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnBrake);
        EnhancedInputComponent->BindAction(InputAsset->BrakeAction, ETriggerEvent::Completed, this, &ACarDriveable::Input_OnBrake);

        EnhancedInputComponent->BindAction(InputAsset->ClutchAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnClutch);
        EnhancedInputComponent->BindAction(InputAsset->ClutchAction, ETriggerEvent::Completed, this, &ACarDriveable::Input_OnClutch);

        EnhancedInputComponent->BindAction(InputAsset->HandbrakeAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnHandbrake);
        EnhancedInputComponent->BindAction(InputAsset->HandbrakeAction, ETriggerEvent::Completed, this, &ACarDriveable::Input_OnHandbrake);

        EnhancedInputComponent->BindAction(InputAsset->ParkAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnPark);
        EnhancedInputComponent->BindAction(InputAsset->HonkAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnHonk);

        EnhancedInputComponent->BindAction(InputAsset->ShiftGearUpAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnGearShiftedUp);

        EnhancedInputComponent->BindAction(InputAsset->ShiftGearDownAction, ETriggerEvent::Triggered, this, &ACarDriveable::Input_OnGearShiftedDown);
    }
}

void ACarDriveable::NotifyControllerChanged()
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

void ACarDriveable::BeginPlay()
{
    Super::BeginPlay();

    check(CommonVehicleMovementComponent);
}

void ACarDriveable::Input_OnSteering(const FInputActionValue& Value)
{
    CommonVehicleMovementComponent->SetSteeringInput(Value.Get<float>());
}

void ACarDriveable::Input_OnThrottle(const FInputActionValue& Value)
{
    CommonVehicleMovementComponent->SetThrottleInput(Value.Get<float>());
}

void ACarDriveable::Input_OnBrake(const FInputActionValue& Value)
{
    CommonVehicleMovementComponent->SetBrakeInput(Value.Get<float>());
}

void ACarDriveable::Input_OnClutch(const FInputActionValue& Value)
{
    CommonVehicleMovementComponent->SetClutchInput(Value.Get<float>());
}

void ACarDriveable::Input_OnHandbrake(const FInputActionValue& Value)
{
    CommonVehicleMovementComponent->SetHandbrakeInput(Value.Get<float>() >= 0.5f);
}

void ACarDriveable::Input_OnPark(const FInputActionValue& Value)
{
    bool bIsParked = CommonVehicleMovementComponent->IsParked();
    CommonVehicleMovementComponent->SetParked(!bIsParked);
}

void ACarDriveable::Input_OnHonk(const FInputActionValue& Value) { /*Honk();*/ }

void ACarDriveable::Input_OnGearShiftedUp(const FInputActionValue& Value)
{
    int32 GearNum = CommonVehicleMovementComponent->GetTargetGear();

    GearNum++;

    CommonVehicleMovementComponent->SetTargetGear(GearNum, true);
}

void ACarDriveable::Input_OnGearShiftedDown(const FInputActionValue& Value)
{
    int32 GearNum = CommonVehicleMovementComponent->GetTargetGear();

    GearNum--;

    CommonVehicleMovementComponent->SetTargetGear(GearNum, true);
}