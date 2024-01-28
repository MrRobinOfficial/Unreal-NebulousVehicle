// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/BoatVehicle.h"

ABoatVehicle::ABoatVehicle(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}