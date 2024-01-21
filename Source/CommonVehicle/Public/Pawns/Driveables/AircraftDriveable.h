// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AircraftDriveable.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API AAircraftDriveable
    : public APawn
{
    GENERATED_BODY()

public:
    AAircraftDriveable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};