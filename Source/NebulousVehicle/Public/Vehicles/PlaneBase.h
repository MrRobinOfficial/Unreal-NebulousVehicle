// Copyright 2023-2024 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/IVehicle.h"
#include "PlaneBase.generated.h"

UCLASS(Abstract, Blueprintable)
class NEBULOUSVEHICLE_API APlaneBase
    : public APawn,
      public IVehicle
{
    GENERATED_BODY()

public:
    /** Name of the SpringArm. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
    static FName SpringArmComponentName;

    /** Name of the Camera. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
    static FName CameraComponentName;

    /** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
    static FName VehicleMeshComponentName;

private:
    /**  The main skeletal mesh associated with this Vehicle */
    UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class USkeletalMeshComponent> Mesh;

    UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class USpringArmComponent> SpringArm;

    UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UCameraComponent> Camera;

public:
    APlaneBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    /** Returns Mesh subobject **/
    class USkeletalMeshComponent* GetMesh() const { return Mesh; }
};