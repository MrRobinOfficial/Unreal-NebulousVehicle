// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IVehicle.generated.h"

UINTERFACE(BlueprintType)
class NEBULOUSVEHICLE_API UVehicle : public UInterface
{
	GENERATED_BODY()
};

class NEBULOUSVEHICLE_API IVehicle
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	FVector GetAcceleration() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	FVector GetVelocity() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	float GetSpeedInKph() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	float GetSpeedInMph() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	bool IsDriveable() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Getters")
	bool IsStopped() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Setters")
	void SetDriveable(bool bEnabled);
};