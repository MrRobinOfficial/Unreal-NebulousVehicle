// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Libraries/PIDLibrary.h"

void UPIDLibrary::TickPID(
        float& LoopOutput,
        FPIDState& PIDState,
        const FPIDConfig& PIDConfig,
        float e,
        float DeltaSeconds)
{
    checkf(DeltaSeconds > 0.0f, TEXT("DeltaSeconds must be greater than 0."));

    float Output = 0.f;

    // Proportional term
    Output += PIDConfig.Kp * e;

    // Integral term
    PIDState.e_Accumulator += e * DeltaSeconds;
    Output += PIDConfig.Ki * PIDState.e_Accumulator;

    // Derivative term 
    float e_Rate = (e - PIDState.LastError) / DeltaSeconds;
    Output += PIDConfig.Kd * e_Rate;
    PIDState.LastError = e;

    LoopOutput = FMath::Clamp(Output, PIDConfig.MinOutput, PIDConfig.MaxOutput);
}

void UPIDLibrary::ResetPID(
        FPIDState& PIDState,
        float NewErrorValue,
        float NewAccumulatorValue)
{
    PIDState.LastError = NewErrorValue;
    PIDState.e_Accumulator = NewAccumulatorValue;
}