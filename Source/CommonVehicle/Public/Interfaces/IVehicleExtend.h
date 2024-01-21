// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IVehicleExtend.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UVehicleExtend : public UInterface
{
	GENERATED_BODY()
};

class COMMONVEHICLE_API IVehicleExtend
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicle Extend|Getters")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicle Extend|Getters")
	float GetMaximumHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicle Extend|Getters")
	float GetNormalizedHealth() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicle Extend|Properties")
	bool IsDestroyed() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Vehicle Extend|Events")
	void Explode();
};