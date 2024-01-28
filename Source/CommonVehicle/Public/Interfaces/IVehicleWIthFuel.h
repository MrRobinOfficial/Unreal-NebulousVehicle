// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IVehicleWithFuel.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UVehicleWithFuel : public UInterface
{
	GENERATED_BODY()
};

class COMMONVEHICLE_API IVehicleWithFuel
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Getters")
	float GetFuelCapacity() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Getters")
	float GetRemainingFuelInLiters() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Getters")
    float GetRemainingFuelAsNormalized() const;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Properties")
    bool IsOutOfFuel() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Properties")
    bool IsLowOnFuel() const;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Events")
    void FillFuel(float DeltaAmount);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fuel System|Events")
    void DrainFuel(float DeltaAmount);
};