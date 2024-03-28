// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WheeledVehiclePawn.h"
#include "Components/CarMovementComponent.h"

#include "Assets/CarInputAsset.h"

#include "Interfaces/ICar.h"
#include "Interfaces/IVehicle.h"

#include "CarBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCarOnDriveableChanged, bool, bOldValue, bool, bNewValue);

UCLASS(Abstract, Blueprintable)
class NEBULOUSVEHICLE_API ACarBase
	: public AWheeledVehiclePawn
	, public IVehicle
	, public ICar
{
	GENERATED_BODY()

public:
	/** Name of the SpringArm. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName SpringArmComponentName;

	/** Name of the Camera. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName CameraComponentName;

protected:
	UPROPERTY(BlueprintAssignable)
	FCarOnDriveableChanged OnDriveableChanged;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
	TObjectPtr<UCarInputAsset> InputAsset;

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = "Details", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UArrowComponent> Arrow;
#endif

	UPROPERTY(Category = "Details", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCarMovementComponent> CarMovementComponent;

	UPROPERTY(Category = "Details", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(Category = "Details", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

protected:
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Variables")
	bool bIsDriveable;

public:
	ACarBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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
	bool IsEngineRunning_Implementation() const;
	bool IsOnAllWheels_Implementation() const;
	bool IsParked_Implementation() const;

	float GetEngineRPM_Implementation() const;
	float GetClutchRatio_Implementation() const;

	float GetSteeringInput_Implementation() const;
	float GetThrottleInput_Implementation() const;
	float GetBrakeInput_Implementation() const;
	float GetClutchInput_Implementation() const;
	bool GetHandbrakeInput_Implementation() const;

	int32 GetGearIndex_Implementation() const;
	int32 GetNumOfGears_Implementation() const;

	void SetSteeringInput_Implementation(float AxisValue);
	void SetThrottleInput_Implementation(float AxisValue);
	void SetBrakeInput_Implementation(float AxisValue);
	void SetClutchInput_Implementation(float AxisValue);
	void SetHandbrakeInput_Implementation(bool bNewValue);
	void SetParkMode_Implementation(bool bNewValue);
	void ShiftToGear_Implementation(int32 GearNum, bool bImmediate);

	void SetEngineEnabled_Implementation(bool bEnabled);
#pragma endregion

#pragma region Input Callbacks
	void Input_OnSteering(const FInputActionValue& Value);
	void Input_OnThrottle(const FInputActionValue& Value);
	void Input_OnBrake(const FInputActionValue& Value);
	void Input_OnClutch(const FInputActionValue& Value);
	void Input_OnHandbrake(const FInputActionValue& Value);
	void Input_OnPark(const FInputActionValue& Value);
	void Input_OnGearShiftedUp(const FInputActionValue& Value);
	void Input_OnGearShiftedDown(const FInputActionValue& Value);
#pragma endregion
};