// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IVehicle.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UVehicle : public UInterface
{
	GENERATED_BODY()
};

class COMMONVEHICLE_API IVehicle
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	FVector GetAcceleration() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	FVector GetVelocity() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeed() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeedInKph() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeedInMph() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Properties")
	bool IsDriveable() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Properties")
	bool IsStopped() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Setters")
	void SetDriveable(bool bEnabled);
};