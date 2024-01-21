// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/Vehicles/CarVehicle.h"

#include "Kismet/GameplayStatics.h"

ACarVehicle::ACarVehicle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ACarVehicle::SetLightState(ELightState NewState)
{
    if (CurrentLightState == NewState)
        return;

    OnLightChanged.Broadcast(CurrentLightState, NewState);

    CurrentLightState = NewState;
}

void ACarVehicle::ToggleLightState()
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

void ACarVehicle::StartHonking()
{
    if (bIsHonking)
        return;

    bIsHonking = true;
}

void ACarVehicle::StopHonking()
{
    if (!bIsHonking)
        return;

    bIsHonking = false;
}

void ACarVehicle::Honk_Implementation()
{
    // TODO: Play honk SFX
}

void ACarVehicle::Explode_Implementation()
{
    if (bIsDestroyed)
        return;

    bIsDestroyed = true;
    OnExplode();
}