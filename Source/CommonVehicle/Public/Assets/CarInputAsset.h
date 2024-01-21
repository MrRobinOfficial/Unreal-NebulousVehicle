// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Assets/VehicleInputAsset.h"
#include "InputAction.h"
#include "CarInputAsset.generated.h"

class UInputAction;

UCLASS()
class COMMONVEHICLE_API UCarInputAsset : public UVehicleInputAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> SteeringAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> ThrottleAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> BrakeAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> ClutchAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> HandbrakeAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> ShiftGearUpAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> ShiftGearDownAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Extra", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> ParkAction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Extra", meta = (DisplayThumbnail = false))
    TObjectPtr<UInputAction> HonkAction;
};