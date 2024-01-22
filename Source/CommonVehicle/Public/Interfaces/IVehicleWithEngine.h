// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IVehicleWithEngine.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UVehicleWithEngine : public UInterface
{
	GENERATED_BODY()
};

class COMMONVEHICLE_API IVehicleWithEngine
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Engine System|Getters")
	float GetEngineRPM() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Engine System|Properties")
	bool IsEngineRunning() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Engine System|Properties")
    bool CanStall() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Engine System|Properties")
    bool CanStart() const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Engine System|Events")
	void StartEngine(bool bForce = true);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Engine System|Events")
	void ShutoffEngine(bool bForce = true);
};