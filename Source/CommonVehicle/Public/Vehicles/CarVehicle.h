// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WheeledVehiclePawn.h"
#include "Components/CarMovementComponent.h"

#include "Interfaces/IVehicle.h"
#include "Interfaces/ICar.h"

#include "Assets/CarInputAsset.h"

#include "CarVehicle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCarOnDriveableChanged, bool, bOldValue, bool, bNewValue);

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarVehicle
    : public AWheeledVehiclePawn
    , public IVehicle
    , public ICar
{
    GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
    FCarOnDriveableChanged OnDriveableChanged;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
    TObjectPtr<class UInputMappingContext> InputMappingContext;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
    TObjectPtr<UCarInputAsset> InputAsset;

protected:
#if WITH_EDITORONLY_DATA
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
    TObjectPtr<class UArrowComponent> Arrow;
#endif

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
    TObjectPtr<UCarMovementComponent> CarMovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Variables")
    bool bIsDriveable;

public:
    ACarVehicle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void NotifyControllerChanged() override;
    void BeginPlay() override;

protected:
#pragma region Vehicle Interface
    FVector GetAcceleration_Implementation() const;
    FVector GetVelocity_Implementation() const;
    float GetSpeed_Implementation() const;
    float GetSpeedInKph_Implementation() const;
    float GetSpeedInMph_Implementation() const;
    bool IsDriveable_Implementation() const;
    bool IsStopped_Implementation() const;
    void SetDriveable_Implementation(bool bEnabled);
#pragma endregion

protected:
#pragma region Car Interface
    bool IsOnAllWheels_Implementation() const;
    float GetSteeringInput_Implementation() const;
    float GetThrottleInput_Implementation() const;
    float GetBrakeInput_Implementation() const;
    float GetClutchInput_Implementation() const;
    bool GetHandbrakeInput_Implementation() const;
    void SetSteeringInput_Implementation(float AxisValue);
    void SetThrottleInput_Implementation(float AxisValue);
    void SetBrakeInput_Implementation(float AxisValue);
    void SetClutchInput_Implementation(float AxisValue);
    void SetHandbrakeInput_Implementation(bool bEnabled);
    float GetEngineRPM_Implementation() const;
    bool IsEngineRunning_Implementation() const;
    void SetEngineEnabled_Implementation(bool bEnabled);
    float GetClutchRatio_Implementation() const;
    int32 GetGearIndex_Implementation() const;
    int32 GetNumOfGears_Implementation() const;
#pragma endregion

protected:
#pragma region Input Callbacks
    void Input_OnSteering(const FInputActionValue& Value);
    void Input_OnThrottle(const FInputActionValue& Value);
    void Input_OnBrake(const FInputActionValue& Value);
    void Input_OnClutch(const FInputActionValue& Value);
    void Input_OnHandbrake(const FInputActionValue& Value);
    void Input_OnPark(const FInputActionValue& Value);
    void Input_OnHonk(const FInputActionValue& Value);
    void Input_OnGearShiftedUp(const FInputActionValue& Value);
    void Input_OnGearShiftedDown(const FInputActionValue& Value);
#pragma endregion

};