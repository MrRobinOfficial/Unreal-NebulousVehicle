// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArcadeLibrary.generated.h"

UCLASS()
class NEBULOUSVEHICLE_API UArcadeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Libraries|Vehicle Library")
	static void SetIntensityForLights(
		const TArray<ULightComponent*> Lights,
		float NewIntensity
	);

	UFUNCTION(BlueprintCallable, Category = "Libraries|Vehicle Library")
	static void SetActiveForLights(
		const TArray<ULightComponent*> Lights,
		bool bNewActive,
		bool bReset = false
	);
};