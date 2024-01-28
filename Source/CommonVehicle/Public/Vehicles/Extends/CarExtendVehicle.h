// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Vehicles/CarVehicle.h"
#include "Interfaces/IVehicleExtend.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CarExtendVehicle.generated.h"

UENUM(BlueprintType)
enum class ELightState : uint8
{
    Off,
    LowBeam,
    HighBeam,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCarLightChanged, ELightState, OldState, ELightState, NewState);

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarExtendVehicle
    : public ACarVehicle
    , public IVehicleExtend
{
    GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
    FOnCarLightChanged OnLightChanged;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
    float MaximumHealth { 1000.0f };

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|VFX")
    TSoftObjectPtr<UParticleSystem> ExplosionFX;

protected:
    UPROPERTY(Transient, VisibleAnywhere, Category = "Variables")
    float CurrentHealth;

    UPROPERTY(Transient, VisibleAnywhere, Category = "Variables")
    bool bIsDestroyed;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Variables")
    ELightState CurrentLightState;

    UPROPERTY(Transient, VisibleAnywhere, Category = "Variables")
    bool bIsHonking;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
    TObjectPtr<UCameraComponent> Camera;

public:
    ACarExtendVehicle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    UFUNCTION(BlueprintPure, Category = "Pawns|Vehicles|Car|Getters")
    FORCEINLINE ELightState GetLightState() const { return CurrentLightState; }

    UFUNCTION(BlueprintPure, Category = "Pawns|Vehicles|Car|Getters")
    FORCEINLINE bool IsHonking() const { return bIsHonking; }

public:
    UFUNCTION(BlueprintCallable, Category = "Pawns|Vehicles|Car|Setters")
    void SetLightState(ELightState NewState);

    UFUNCTION(BlueprintCallable, Category = "Pawns|Vehicles|Car|Setters")
    void ToggleLightState();

public:
    UFUNCTION(BlueprintCallable, Category = "Pawns|Vehicles|Car")
    void StartHonking();

    UFUNCTION(BlueprintCallable, Category = "Pawns|Vehicles|Car")
    void StopHonking();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pawns|Vehicles|Car")
    void Honk();

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (BlueprintProtected))
    void OnExplode();

protected:
    float GetCurrentHealth_Implementation() const { return CurrentHealth; }
    float GetMaximumHealth_Implementation() const { return MaximumHealth; }
    float GetNormalizedHealth_Implementation() const { return CurrentHealth / MaximumHealth; }
    bool IsDestroyed_Implementation() const { return bIsDestroyed; }
    void Explode_Implementation();
};