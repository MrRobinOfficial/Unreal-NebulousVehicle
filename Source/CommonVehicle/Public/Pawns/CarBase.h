// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Interfaces/IVehicle.h"
#include "CarBase.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarBase
    : public AWheeledVehiclePawn
    , public IVehicle
{
    GENERATED_BODY()

public:
    ACarBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class UArrowComponent> Arrow;
#endif

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<class UCommonVehicleMovementComponent> CommonVehicleMovementComponent;
};