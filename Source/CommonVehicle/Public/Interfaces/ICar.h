// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ICar.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UCar : public UInterface
{
	GENERATED_BODY()
};

class COMMONVEHICLE_API ICar
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters")
	TArray<int32> GetWheels() const; // Return wheel collection

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Properties")
	bool IsOnAllWheels() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Input")
	float GetSteeringInput() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Input")
	float GetThrottleInput() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Input")
	float GetBrakeInput() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Input")
	float GetClutchInput() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Input")
	bool GetHandbrakeInput() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Setters|Input")
	void SetSteeringInput(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Setters|Input")
	void SetThrottleInput(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Setters|Input")
	void SetBrakeInput(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Setters|Input")
	void SetClutchInput(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Setters|Input")
	void SetHandbrakeInput(bool bEnabled);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Engine")
	float GetEngineRPM() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Properties|Engine")
	bool IsEngineRunning() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Setters|Engine")
	void SetEngineEnabled(bool bEnabled);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Clutch")
	float GetClutchRatio() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Gearbox")
	int32 GetGearIndex() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car|Getters|Gearbox")
	int32 GetNumOfGears() const;
};