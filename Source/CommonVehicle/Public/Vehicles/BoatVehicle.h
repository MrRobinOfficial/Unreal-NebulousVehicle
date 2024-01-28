// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/IVehicle.h"
#include "BoatVehicle.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FBoatReq);

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ABoatVehicle
    : public APawn,
    public IVehicle
{
    GENERATED_BODY()

public:
    ABoatVehicle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};