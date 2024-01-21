// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BoatDriveable.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ABoatDriveable
    : public APawn
{
    GENERATED_BODY()

public:
    ABoatDriveable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};