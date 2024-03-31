// Copyright 2023-2024 MrRobin. All Rights Reserved.

// Credits to gamedevtricks's blog (https://gamedevtricks.com/post/pid-controllers/)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PIDLibrary.generated.h"

USTRUCT(BlueprintType)
struct FPIDState
{
    GENERATED_BODY()

public:
    UPROPERTY(Transient)
    float LastError;

    UPROPERTY(Transient)
    float e_Accumulator;
};

USTRUCT(BlueprintType)
struct FPIDConfig
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Kp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Ki;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Kd;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinOutput;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxOutput;
};

UCLASS()
class NEBULOUSVEHICLE_API UPIDLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Libraries|PID Library")
    /**
     * Updates the PID controller and calculates the output value for the next loop iteration.
     *
     * @param LoopOutput A reference to the variable that will store the output value of the PID controller.
     * @param PIDState A reference to the PID state object that holds the current state of the PID controller.
     * @param PIDConfig The PID configuration object that contains the parameters of the PID controller.
     * @param e The error value calculated by the PID controller.
     * @param DeltaSeconds The time difference between the current and previous loop iterations.
     *
     * @throws None
     */
    static void TickPID(
        float& LoopOutput,
        UPARAM(ref) FPIDState& PIDState,
        const FPIDConfig& PIDConfig,
        float e,
        float DeltaSeconds
    );

    UFUNCTION(BlueprintCallable, Category = "Libraries|PID Library")
    /**
     * Resets the PID controller state with the new error and accumulator values.
     *
     * @param PIDState reference to the PID controller state
     * @param NewErrorValue the new error value
     * @param NewAccumulatorValue the new accumulator value (default = 0.0f)
     */
    static void ResetPID(
        UPARAM(ref) FPIDState& PIDState,
        float NewErrorValue,
        float NewAccumulatorValue = 0.0f
    );
};