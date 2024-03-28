// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameplayTagContainer.h"
#include "Interfaces/IVehicle.h"

#include "VehicleLibrary.generated.h"

UCLASS()
class NEBULOUSVEHICLE_API UVehicleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Libraries|Vehicle Library")
	static TArray<AActor*> FindAllVehiclesFromTag(FGameplayTag Tag);
};