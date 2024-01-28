// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/Extends/CarExtendVehicle.h"
//#include "Components/CarMovementComponent.h"

#include "Kismet/GameplayStatics.h"

ACarExtendVehicle::ACarExtendVehicle(const FObjectInitializer& ObjectInitializer)
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

void ACarExtendVehicle::SetLightState(ELightState NewState)
{
    if (CurrentLightState == NewState)
        return;

    OnLightChanged.Broadcast(CurrentLightState, NewState);

    CurrentLightState = NewState;
}

void ACarExtendVehicle::ToggleLightState()
{
    switch (CurrentLightState)
    {
        case ELightState::Off:
            SetLightState(ELightState::LowBeam);
            break;

        case ELightState::LowBeam:
            SetLightState(ELightState::HighBeam);
            break;

        case ELightState::HighBeam:
            SetLightState(ELightState::Off);
            break;
    }
}

void ACarExtendVehicle::StartHonking()
{
    if (bIsHonking)
        return;

    bIsHonking = true;
}

void ACarExtendVehicle::StopHonking()
{
    if (!bIsHonking)
        return;

    bIsHonking = false;
}

void ACarExtendVehicle::Honk_Implementation()
{
    // TODO: Play honk SFX
}

void ACarExtendVehicle::Explode_Implementation()
{
    if (bIsDestroyed)
        return;

    bIsDestroyed = true;
    OnExplode();
}