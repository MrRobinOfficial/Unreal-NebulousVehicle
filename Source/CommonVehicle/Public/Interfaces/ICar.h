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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Getters")
	float GetEngineRPM() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Properties")
	bool IsEngineRunning() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Events")
	void StartEngine();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle|Events")
	void ShutoffEngine();
};