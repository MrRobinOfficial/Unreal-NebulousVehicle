// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "CarMovementComponent.generated.h"

class COMMONVEHICLE_API UCommonChaosWheeledVehicleSimulation
    : public UChaosWheeledVehicleSimulation
{
public:
    void FillOutputState(FChaosVehicleAsyncOutput& Output) override;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEngineStateChangedSignature, bool, bOldState, bool, bNewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGearChangedSignature, int32, OldGearNum, int32, NewGearNum);

UCLASS(ClassGroup = (Physics), meta = (BlueprintSpawnableComponent), 
    HideCategories = (PlanarMovement, "Components|Movement|Planar", Activation, 
    "Components|Activation"))
class COMMONVEHICLE_API UCarMovementComponent : public UChaosWheeledVehicleMovementComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintAssignable)
    FOnEngineStateChangedSignature OnEngineStateChanged;

    UPROPERTY(BlueprintAssignable)
    FOnGearChangedSignature OnGearChanged;

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
    float ClutchEngageThreshold = 0.5f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
    float ClutchDisengageFactor = 0.1f;

protected:
    UPROPERTY(BlueprintReadOnly, Transient, Category = "Variables")
    float RawClutchInput;

public:
    UCarMovementComponent();

protected:
    void ClearRawInput() override;

    ///** */
    TUniquePtr<Chaos::FSimpleWheeledVehicle> CreatePhysicsVehicle() override
    {
        // Make the Vehicle Simulation class that will be updated from the physics thread async callback
        VehicleSimulationPT = MakeUnique<UCommonChaosWheeledVehicleSimulation>();

        return UChaosVehicleMovementComponent::CreatePhysicsVehicle();
    }

public:
    /**  */
    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE float GetClutchInput() const { return RawClutchInput; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE float GetTorqueReductionFactor() const
    {
        if (RawClutchInput >= ClutchEngageThreshold)
            return 1.0f;

        return FMath::GetMappedRangeValueClamped(
            FVector2D(0.0f, ClutchEngageThreshold),
            FVector2D(1.0f, ClutchDisengageFactor),
            RawClutchInput
        );
    }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE float GetEngineRPM() const
    {
        float EngineRPM = 0.f;

        if (bMechanicalSimEnabled && PVehicleOutput)
        {
            EngineRPM = PVehicleOutput->EngineRPM;
        }

        return EngineRPM;
    }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE float GetEngineIdleRPM() const { return EngineSetup.EngineIdleRPM; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE float GetEngineMaxRPM() const { return EngineSetup.MaxRPM; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE float GetEngineMaxTorque() const { return EngineSetup.MaxTorque; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE FRuntimeFloatCurve GetEngineCurve() const { return EngineSetup.TorqueCurve; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement")
    FORCEINLINE bool GetEngineState() const { return  bMechanicalSimEnabled; }

public:
    UFUNCTION(BlueprintPure = false, Category = "Game|Components|CarMovement")
    FORCEINLINE FVector GetAcceleration() const { return FVector::ZeroVector; }

    UFUNCTION(BlueprintPure = false, Category = "Game|Components|CarMovement")
    FORCEINLINE FVector GetVelocity() const { return FVector::ZeroVector; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement", meta = (DisplayName = "Get Forward Speed [m/s]"))
    FORCEINLINE float GetSpeedInCM() const { return GetForwardSpeed() * UE_CM_TO_M; }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement", meta = (DisplayName = "Get Forward Speed [km/h]"))
    FORCEINLINE float GetSpeedInKPH() const { return Chaos::CmSToKmH(GetForwardSpeed()); }

    UFUNCTION(BlueprintPure, Category = "Game|Components|CarMovement", meta = (DisplayName = "Get Forward Speed [mph]"))
    FORCEINLINE float GetSpeedInMPH() const { return Chaos::CmSToMPH(GetForwardSpeed()); }

public:
    UFUNCTION(BlueprintCallable, Category="Game|Components|CarMovement")
    void SetClutchInput(float Clutch);

    UFUNCTION(BlueprintCallable, Category="Game|Components|CarMovement")
    void IncreaseClutchInput(float ClutchDelta);

    UFUNCTION(BlueprintCallable, Category="Game|Components|CarMovement")
    void DecreaseClutchInput(float ClutchDelta);

public:
    UFUNCTION(BlueprintCallable, Category = "Game|Components|CarMovement")
    void ToggleEngineState();

    UFUNCTION(BlueprintCallable, Category="Game|Components|CarMovement")
    void SetEngineState(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Game|Components|CarMovement")
    float GetTorqueFromRPM(float EngineRPM);
};