// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/HelicopterVehicle.h"

AHelicopterVehicle::AHelicopterVehicle(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}