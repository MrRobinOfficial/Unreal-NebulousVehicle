// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/IVehicle.h"
#include "AircraftBase.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API AAircraftBase
    : public APawn
    , public IVehicle
{
    GENERATED_BODY()

public:
    AAircraftBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};