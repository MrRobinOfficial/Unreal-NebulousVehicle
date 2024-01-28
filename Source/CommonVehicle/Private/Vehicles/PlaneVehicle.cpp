// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/PlaneVehicle.h"

APlaneVehicle::APlaneVehicle(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}