// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Interfaces/IVehicle.h"
#include "CarBase.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarBase
    : public AWheeledVehiclePawn
    , public IVehicle
    , public IVehicleWithEngine
    , public ICar
{
    GENERATED_BODY()

#if WITH_EDITORONLY_DATA
protected:
    UPROPERTY(VisibleAnywhere, Category = "Variables")
    TObjectPtr<class UArrowComponent> Arrow;
#endif

protected:
    UPROPERTY(VisibleAnywhere, Category = "Variables")
    TObjectPtr<class UCarMovementComponent> CarMovementComponent;

public:
    ACarBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    UFUNCTION(BlueprintPure, Category = "Pawns|Vehicles|Car Base|Getters")
    UCarMovementComponent* GetCarMovement() const { return CarMovementComponent; }

protected:
#pragma region Vehicle Interface
	float GetMass_Implementation() const
	float GetSpeed_Implementation() const;
	float GetSpeedInCM_Implementation() const;
	float GetSpeedInKPH_Implementation() const;
	float GetSpeedInMPH_Implementation() const;
	float GetSpeedInKN_Implementation() const;
	FVector GetVelocity_Implementation() const;
	FVector GetAcceleration_Implementation() const;
	FVector GetVelocityInCM_Implementation() const;
	FVector GetAccelerationInCM_Implementation() const;
#pragma endregion

#pragma region Engine Interface
    float IsEngineRunning_Implementation() const;

    void StartEngine_Implementation();
    void ShutoffEngine_Implementation();
#pragma endregion
};