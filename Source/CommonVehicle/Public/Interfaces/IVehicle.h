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
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle")
	//void Honk();
};