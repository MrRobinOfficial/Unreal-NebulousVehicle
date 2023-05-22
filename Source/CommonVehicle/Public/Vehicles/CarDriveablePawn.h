// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarPawn.h"
#include "CarDriveablePawn.generated.h"

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarDriveablePawn : public ACarPawn
{
    GENERATED_BODY()

public:
    ACarDriveablePawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    //virtual void BeginPlay() override;
    //virtual void Tick(float DeltaSeconds) override;
    //virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class USpringArmComponent> SpringArm;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class UCameraComponent> Camera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputMappingContext> CarMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> SteeringAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> ThrottleAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> BrakeAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> ClutchAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> HandbrakeAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> ParkAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> HonkAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> ShiftGearUpAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
    TObjectPtr<class UInputAction> ShiftGearDownAction;

protected:
	UFUNCTION()
    void OnSteeringAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnThrottleAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnBrakeAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnClutchAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnHandbrakeAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnParkAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnHonkAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnGearShiftedUpAction(const FInputActionValue& Value);

    UFUNCTION()
    void OnGearShiftedDownAction(const FInputActionValue& Value);
};