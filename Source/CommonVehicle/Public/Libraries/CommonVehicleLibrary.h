// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameplayTagContainer.h"
#include "Interfaces/IVehicle.h"

#include "CommonVehicleLibrary.generated.h"

UCLASS()
class COMMONVEHICLE_API UCommonVehicleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Common Vehicle|Libraries|Common Vehicle Library")
	static TArray<AActor*> FindAllVehiclesFromTag(FGameplayTag Tag);
};