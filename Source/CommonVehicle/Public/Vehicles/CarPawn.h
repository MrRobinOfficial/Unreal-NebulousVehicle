// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CarPawn.generated.h"

UENUM(BlueprintType)
enum class ELightState : uint8
{
    Off,
    LowBeam,
    HighBeam,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCarPawnOnLightStateChanged, ELightState, OldState, ELightState, NewState);

UCLASS(Abstract, Blueprintable)
class COMMONVEHICLE_API ACarPawn : public AWheeledVehiclePawn
{
    GENERATED_BODY()

public:
    ACarPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintAssignable)
    FCarPawnOnLightStateChanged OnLightStateChanged;

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Car Pawn")
    FORCEINLINE ELightState GetLightState() const { return LightState; }

public:
    UFUNCTION(BlueprintCallable, Category = "Car Pawn")
    void SetLightState(ELightState NewState);

    UFUNCTION(BlueprintCallable, Category = "Car Pawn")
    void ToggleLightState();

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Car Pawn")
    void Honk();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Car Pawn")
    void Explode();
    
protected:
    //virtual void BeginPlay() override;
    //virtual void Tick(float DeltaSeconds) override;
    //virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    //virtual void PossessedBy(AController* NewController) override;
    //virtual void UnPossessed() override;

    virtual void Explode_Implementation() override;

protected:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class UArrowComponent> Arrow;
#endif

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<class UCommonVehicleMovementComponent> CommonVehicleMovementComponent;

protected:
    UPROPERTY(Transient)
    ELightState LightState;
};