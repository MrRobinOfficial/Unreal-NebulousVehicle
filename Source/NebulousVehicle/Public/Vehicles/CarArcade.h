// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/CarBase.h"
#include "CarArcade.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FCarMaterials
{
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	TArray<TObjectPtr<class UMaterialInstanceDynamic>> Materials;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	FName MaterialParameterName { TEXT("Intensity") };

public:
	void SetIntensity(float Intensity)
	{
		for (UMaterialInstanceDynamic* Material : Materials)
			Material->SetScalarParameterValue(MaterialParameterName, Intensity);
	}
}

USTRUCT(BlueprintType)
struct FCarLights
{
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	TArray<TObjectPtr<class ULightComponent>> Lights;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	FCarMaterials Materials;
};

USTRUCT(BlueprintType)
struct FCarBrakeDisc
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Visuals")
	FCarMaterials Materials;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float Intensity { 1300.0f };

	/* The amount of seconds for brake disc to turn to red, during a heavy loaded brake. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (ForceUnits = "seconds", ClampMin = "0", UIMin = "0"))
	float SpinUp { 2.5f };

	/* The amount of seconds for the brake disc to turn to normal, during a release of the brakes. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (ForceUnits = "seconds", ClampMin = "0", UIMin = "0"))
	float SpinDown { 5.5f };
};

USTRUCT(BlueprintType)
struct FCarHeadlight
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	FCarLights Lights;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float LowIntensity { 700.0f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float HighIntensity { 1300.0f };
};

USTRUCT(BlueprintType)
struct FCarTaillight
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	FCarLights Lights;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float Intensity { 700.0f };
};

UENUM(BlueprintType)
enum class EHeadlightState : uint8
{
	Off,
	LowBeam,
	HighBeam,
};

// HIGH PRIORITIES:
// TODO: Add tire marks
// TODO: Add AI support (chase player, drive through checkpoints, don't collide with anything, park, etc)
// TODO: Add support for steering wheel input devices
// TODO: Add fuel consumption
// TODO: Add speed limiter and cruise control (PID Controllers) 
// TODO: Add engine sound, transmission sound and environment sounds

// MEDIUM PRIORITIES:
// TODO: Create telemetry tool
// TODO: Add car builder tool (with real world references)
// TODO: Add support for ragdolling

// LOW PRIORITIES:
// TODO: Add support character animations
// TODO: Make FOV camera (like NFS SHIFT 2 UNLEASHED)
// TODO: Make orbit camera (like GTA or NFS Unbound)
// TODO: Add support for entering/exiting the vehicle
// TODO: Add support for mods (.ini files)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCarOnHeadlightChanged, EHeadlightState, OldState, EHeadlightState, NewState);

UCLASS(Abstract, Blueprintable)
class NEBULOUSVEHICLE_API ACarArcade
	: public ACarBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
	FCarOnHeadlightChanged OnHeadlightChanged;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Visuals")
	FCarHeadlight Headlight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Visuals")
	FCarTaillight Taillight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Visuals")
	FCarBrakeDisc BrakeDisc;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Emitters")
	TObjectPtr<UNiagaraEmitter> BackfireEmitter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Emitters")
	TObjectPtr<UNiagaraEmitter> ScratchEmitter;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
	TObjectPtr<class UInputMappingContext> ArcadeInputMappingContext;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> HeadlightAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> HonkAction;

private:
	UPROPERTY(Category = "Details", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EHeadlightState HeadlightState;

public:
	ACarArcade(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void NotifyControllerChanged() override;

public:
	UFUNCTION(BlueprintPure, Category = "Vehicles|Car|Getters")
	FORCEINLINE EHeadlightState GetHeadlightState() const { return HeadlightState; }

public:
	UFUNCTION(BlueprintCallable, Category = "Vehicles|Car|Setters")
	void SetHeadlightState(EHeadlightState NewState);

protected:
#pragma region Input Functions
	void SetBrakeInput_Implementation(float AxisValue);
#pragma endregion

#pragma region Input Callbacks
	void Input_OnHeadlight(const FInputActionValue& Value);
	void Input_OnHonk(const FInputActionValue& Value);
#pragma endregion
};