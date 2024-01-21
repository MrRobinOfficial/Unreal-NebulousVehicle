// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HelicopterDriveable.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API AHelicopterDriveable
    : public APawn
{
    GENERATED_BODY()

public:
    AHelicopterDriveable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};