// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/AircraftBase.h"

AAircraftBase::AAircraftBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}