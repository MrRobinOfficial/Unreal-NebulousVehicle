// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RacerComponent.generated.h"

UCLASS(ClassGroup = (Physics), meta = (BlueprintSpawnableComponent),
       HideCategories = (PlanarMovement, "Components|Movement|Planar", Activation))
class NEBULOUSVEHICLE_API URacerComponent final : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, Transient, Category = "Variables")
    FTransform CheckpointTransform;

    UPROPERTY(VisibleAnywhere, Transient, Category = "Variables")
    int32 CheckpointIndex;

    UPROPERTY(VisibleAnywhere, Transient, Category = "Variables")
    int32 LapIndex;

public:
    UFUNCTION(BlueprintPure, Category = "Components|Racer")
    FORCEINLINE FTransform GetCheckpointTransform() const { return CheckpointTransform; }

    UFUNCTION(BlueprintPure, Category = "Components|Racer")
    FORCEINLINE int32 GetCheckpointIndex() const { return CheckpointIndex; }

    UFUNCTION(BlueprintPure, Category = "Components|Racer")
    FORCEINLINE int32 GetLapIndex() const { return LapIndex; }

public:
    void OnCheckpointReached(
        const FTransform &NewTransform,
        const int32 &NewIndex,
        const bool bIsLastCheckpoint);

public:
    UFUNCTION(BlueprintCallable, Category = "Components|Racer")
    void Respawn();

    /**
     * Calculates the score based on the lap, checkpoint and distance between the racer and checkpoint.
     *
     * @return The calculated score.
     */
    UFUNCTION(BlueprintPure = false, Category = "Components|Racer",
              meta = (DisplayName = "Calculate Score", CompactNodeTitle = "CalcScore"))
    float CalcScore() const;
};