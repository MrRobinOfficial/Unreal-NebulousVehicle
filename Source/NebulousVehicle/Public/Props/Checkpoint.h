// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class NEBULOUSVEHICLE_API ACheckpoint : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
    float Radius{5.0f};

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
    int32 Index{0};

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Details")
    bool bIsLastCheckpoint{false};

private:
    UPROPERTY(Category = "Details", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class USphereComponent> Collision;

public:
    ACheckpoint();

protected:
    void BeginPlay() override;

    void OnOverlapBegin(
        class UPrimitiveComponent *OverlappedComp,
        class AActor *OtherActor,
        class UPrimitiveComponent *OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult &SweepResult);
};