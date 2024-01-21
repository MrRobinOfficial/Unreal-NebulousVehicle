// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Pawns/CarBase.h"
#include "Assets/CarInputAsset.h"

#include "CarDriveable.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarDriveable : public ACarBase
{
    GENERATED_BODY()

public:
    ACarDriveable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void NotifyControllerChanged() override;
    void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class USpringArmComponent> SpringArm;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class UCameraComponent> Camera;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
    TObjectPtr<class UInputMappingContext> InputMappingContext;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details|Input", meta = (DisplayThumbnail = false))
    TObjectPtr<UCarInputAsset> InputAsset;

protected:
    void Input_OnSteering(const FInputActionValue& Value);
    void Input_OnThrottle(const FInputActionValue& Value);
    void Input_OnBrake(const FInputActionValue& Value);
    void Input_OnClutch(const FInputActionValue& Value);
    void Input_OnHandbrake(const FInputActionValue& Value);
    void Input_OnPark(const FInputActionValue& Value);
    void Input_OnHonk(const FInputActionValue& Value);
    void Input_OnGearShiftedUp(const FInputActionValue& Value);
    void Input_OnGearShiftedDown(const FInputActionValue& Value);
};