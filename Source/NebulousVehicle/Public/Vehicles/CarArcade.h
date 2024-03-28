// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/CarBase.h"
#include "CarArcade.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FCarHeadlight
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	TArray<TObjectPtr<class ULightComponent>> Lights;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "asd", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float LowIntensity { 700.0f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "asd", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float HighIntensity { 1300.0f };
};

USTRUCT(BlueprintType)
struct FCarTaillight
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	TArray<TObjectPtr<class ULightComponent>> Lights;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "asd", meta = (ForceUnits = "Lumens", ClampMin = "0", UIMin = "0"))
	float Intensity { 700.0f };
};

UENUM(BlueprintType)
enum class EHeadlightState : uint8
{
	Off,
	LowBeam,
	HighBeam,
};

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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	FCarHeadlight Headlight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
	FCarTaillight Taillight;

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