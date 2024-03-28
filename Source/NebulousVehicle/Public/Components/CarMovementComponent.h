// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "CarMovementComponent.generated.h"

class NEBULOUSVEHICLE_API UCommonChaosWheeledVehicleSimulation
    : public UChaosWheeledVehicleSimulation
{
public:
    void FillOutputState(FChaosVehicleAsyncOutput& Output) override;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEngineStateChangedSignature, bool, bOldState, bool, bNewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGearChangedSignature, int32, OldGearNum, int32, NewGearNum);

UCLASS(ClassGroup = (Physics), meta = (BlueprintSpawnableComponent), 
    HideCategories = (PlanarMovement, "Components|Movement|Planar", Activation))
class NEBULOUSVEHICLE_API UCarMovementComponent : public UChaosWheeledVehicleMovementComponent
{
    GENERATED_BODY()

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
    FORCEINLINE float GetClutchInput() const { return RawClutchInput; }

    FORCEINLINE float GetEngineIdleRPM() const { return EngineSetup.EngineIdleRPM; }

    FORCEINLINE float GetEngineMaxRPM() const { return EngineSetup.MaxRPM; }

    FORCEINLINE float GetEngineMaxTorque() const { return EngineSetup.MaxTorque; }

    FORCEINLINE FRuntimeFloatCurve GetEngineCurve() const { return EngineSetup.TorqueCurve; }

public:
    void SetClutchInput(float Clutch);

    void IncreaseClutchInput(float ClutchDelta);

    void DecreaseClutchInput(float ClutchDelta);

public:
    void ToggleEngineState();

    void SetEngineState(bool bEnabled);

    float GetTorqueFromRPM(float EngineRPM);
};