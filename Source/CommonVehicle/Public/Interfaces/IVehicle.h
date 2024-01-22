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
	float GetMass() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeed() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeedInCM() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeedInKPH() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeedInMPH() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetSpeedInKN() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	FVector GetVelocity() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	FVector GetAcceleration() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	FVector GetVelocityInCM() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	FVector GetAccelerationInCM() const;
};