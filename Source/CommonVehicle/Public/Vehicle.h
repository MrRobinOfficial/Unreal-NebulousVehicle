// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "Vehicle.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UVehicle : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class COMMONVEHICLE_API IVehicle
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle")
	void Honk();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle")
	void Explode();
};