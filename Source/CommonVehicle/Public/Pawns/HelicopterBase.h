// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/IVehicle.h"
#include "HelicopterBase.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API AHelicopterBase
    : public APawn
    , public IVehicle
{
    GENERATED_BODY()

public:
    AHelicopterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};