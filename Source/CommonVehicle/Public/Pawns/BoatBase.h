// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/IVehicle.h"
#include "BoatBase.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ABoatBase
    : public APawn,
    public IVehicle
{
    GENERATED_BODY()

public:
    ABoatBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};