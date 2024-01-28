// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ICarExtend.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UCarExtend : public UInterface
{
	GENERATED_BODY()
};

class COMMONVEHICLE_API ICarExtend
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car Extend|Getters|Fuel")
	float GetFuelCapacity() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car Extend|Getters|Fuel")
	float GetRemainingFuel() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car Extend|Getters|Fuel")
	float GetRemainingFuelAsNormalized() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car Extend|Properties|Fuel")
	bool IsLowOnFuel() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Car Extend|Properties|Fuel")
	bool IsOutOfFuel() const;
};