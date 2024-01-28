// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/CarVehicle.h"

#if WITH_EDITOR
#include "Components/ArrowComponent.h"
#endif

#include "Utils/CommonVehicleUnits.h"

// %% EnhancedInput Module %%
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACarVehicle::ACarVehicle(const FObjectInitializer& ObjectInitializer)
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
}

void ACarVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(InputAsset->SteeringAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnSteering);
        EnhancedInputComponent->BindAction(InputAsset->SteeringAction, ETriggerEvent::Completed, this, &ACarVehicle::Input_OnSteering);

        EnhancedInputComponent->BindAction(InputAsset->ThrottleAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnThrottle);
        EnhancedInputComponent->BindAction(InputAsset->ThrottleAction, ETriggerEvent::Completed, this, &ACarVehicle::Input_OnThrottle);

        EnhancedInputComponent->BindAction(InputAsset->BrakeAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnBrake);
        EnhancedInputComponent->BindAction(InputAsset->BrakeAction, ETriggerEvent::Completed, this, &ACarVehicle::Input_OnBrake);

        EnhancedInputComponent->BindAction(InputAsset->ClutchAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnClutch);
        EnhancedInputComponent->BindAction(InputAsset->ClutchAction, ETriggerEvent::Completed, this, &ACarVehicle::Input_OnClutch);

        EnhancedInputComponent->BindAction(InputAsset->HandbrakeAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnHandbrake);
        EnhancedInputComponent->BindAction(InputAsset->HandbrakeAction, ETriggerEvent::Completed, this, &ACarVehicle::Input_OnHandbrake);

        EnhancedInputComponent->BindAction(InputAsset->ParkAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnPark);
        EnhancedInputComponent->BindAction(InputAsset->HonkAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnHonk);

        EnhancedInputComponent->BindAction(InputAsset->ShiftGearUpAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnGearShiftedUp);

        EnhancedInputComponent->BindAction(InputAsset->ShiftGearDownAction, ETriggerEvent::Triggered, this, &ACarVehicle::Input_OnGearShiftedDown);
    }
}

void ACarVehicle::NotifyControllerChanged()
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

void ACarVehicle::BeginPlay()
{
    Super::BeginPlay();

    bIsDriveable = true;
}

#pragma region Vehicle Interface
FVector ACarVehicle::GetAcceleration_Implementation() const
{
    return CarMovementComponent->GetAcceleration();
}

FVector ACarVehicle::GetVelocity_Implementation() const
{
    return CarMovementComponent->GetVelocity();
}

float ACarVehicle::GetSpeed_Implementation() const
{
    return CarMovementComponent->GetVelocity() | GetActorForwardVector();
}

float ACarVehicle::GetSpeedInKph_Implementation() const
{
    const float Speed = CarMovementComponent->GetVelocity() | GetActorForwardVector();
    return Speed * VEH_METER_PER_SECOND_TO_KPH;
}

float ACarVehicle::GetSpeedInMph_Implementation() const
{
    const float Speed = CarMovementComponent->GetVelocity() | GetActorForwardVector();
    return Speed * VEH_METER_PER_SECOND_TO_MPH;
}

bool ACarVehicle::IsDriveable_Implementation() const
{
    return bIsDriveable;
}

bool ACarVehicle::IsStopped_Implementation() const
{
    return false;
}

void ACarVehicle::SetDriveable_Implementation(bool bEnabled)
{
    if (bIsDriveable == bEnabled)
        return;

    OnDriveableChanged.Broadcast(bIsDriveable, bEnabled);

    bIsDriveable = bEnabled;
}
#pragma endregion

#pragma region Car Interface
bool ACarVehicle::IsOnAllWheels_Implementation() const
{
    return false;
}

float ACarVehicle::GetSteeringInput_Implementation() const
{
    return CarMovementComponent->GetSteeringInput();
}

float ACarVehicle::GetThrottleInput_Implementation() const
{
    return CarMovementComponent->GetThrottleInput();
}

float ACarVehicle::GetBrakeInput_Implementation() const
{
    return CarMovementComponent->GetBrakeInput();
}

float ACarVehicle::GetClutchInput_Implementation() const
{
    return CarMovementComponent->GetThrottleInput();
}

bool ACarVehicle::GetHandbrakeInput_Implementation() const
{
    return CarMovementComponent->GetHandbrakeInput();
}

void ACarVehicle::SetSteeringInput_Implementation(float AxisValue)
{
    CarMovementComponent->SetSteeringInput(AxisValue);
}

void ACarVehicle::SetThrottleInput_Implementation(float AxisValue)
{
    CarMovementComponent->SetThrottleInput(AxisValue);
}

void ACarVehicle::SetBrakeInput_Implementation(float AxisValue)
{
    CarMovementComponent->SetBrakeInput(AxisValue);
}

void ACarVehicle::SetClutchInput_Implementation(float AxisValue)
{
    CarMovementComponent->SetSteeringInput(AxisValue);
}

void ACarVehicle::SetHandbrakeInput_Implementation(bool bEnabled)
{
    CarMovementComponent->SetHandbrakeInput(bEnabled);
}

float ACarVehicle::GetEngineRPM_Implementation() const
{
    return 0.0f;
}

bool ACarVehicle::IsEngineRunning_Implementation() const
{
    return false;
}

void ACarVehicle::SetEngineEnabled_Implementation(bool bEnabled)
{

}

float ACarVehicle::GetClutchRatio_Implementation() const
{
    return 0.0f;
}

int32 ACarVehicle::GetGearIndex_Implementation() const
{
    return -1;
}

int32 ACarVehicle::GetNumOfGears_Implementation() const
{
    return -1;
}
#pragma endregion

#pragma region Input Callbacks
void ACarVehicle::Input_OnSteering(const FInputActionValue& Value)
{
    CarMovementComponent->SetSteeringInput(Value.Get<float>());
}

void ACarVehicle::Input_OnThrottle(const FInputActionValue& Value)
{
    CarMovementComponent->SetThrottleInput(Value.Get<float>());
}

void ACarVehicle::Input_OnBrake(const FInputActionValue& Value)
{
    CarMovementComponent->SetBrakeInput(Value.Get<float>());
}

void ACarVehicle::Input_OnClutch(const FInputActionValue& Value)
{
    CarMovementComponent->SetClutchInput(Value.Get<float>());
}

void ACarVehicle::Input_OnHandbrake(const FInputActionValue& Value)
{
    CarMovementComponent->SetHandbrakeInput(Value.Get<float>() >= 0.5f);
}

void ACarVehicle::Input_OnPark(const FInputActionValue& Value)
{
    bool bIsParked = CarMovementComponent->IsParked();
    CarMovementComponent->SetParked(!bIsParked);
}

void ACarVehicle::Input_OnHonk(const FInputActionValue& Value) { /*Honk();*/ }

void ACarVehicle::Input_OnGearShiftedUp(const FInputActionValue& Value)
{
    int32 GearNum = CarMovementComponent->GetTargetGear();

    GearNum++;

    CarMovementComponent->SetTargetGear(GearNum, true);
}

void ACarVehicle::Input_OnGearShiftedDown(const FInputActionValue& Value)
{
    int32 GearNum = CarMovementComponent->GetTargetGear();

    GearNum--;

    CarMovementComponent->SetTargetGear(GearNum, true);
}
#pragma endregion