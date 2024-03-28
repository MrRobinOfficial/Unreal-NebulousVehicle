// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ICar.generated.h"

UINTERFACE(BlueprintType)
class NEBULOUSVEHICLE_API UCar : public UInterface
{
	GENERATED_BODY()
};

class NEBULOUSVEHICLE_API ICar
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	bool IsParked() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	bool IsEngineRunning() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	bool IsOnAllWheels() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	float GetEngineRPM() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	float GetClutchRatio() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	float GetSteeringInput() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	float GetThrottleInput() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	float GetBrakeInput() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	float GetClutchInput() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	bool GetHandbrakeInput() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	int32 GetGearIndex() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Getters")
	int32 GetNumOfGears() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetSteeringInput(float AxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetThrottleInput(float AxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetBrakeInput(float AxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetClutchInput(float AxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetHandbrakeInput(bool bNewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetParkMode(bool bNewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void ShiftToGear(int32 GearNum, bool bImmediate);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicles|Car|Setters")
	void SetEngineEnabled(bool bEnabled);
};