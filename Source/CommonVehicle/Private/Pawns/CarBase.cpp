// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/CarBase.h"

#include "Components/ArrowComponent.h"
#include "Components/CommonVehicleMovementComponent.h"

ACarBase::ACarBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCarMovementComponent>(AWheeledVehiclePawn::VehicleMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    CommonVehicleMovementComponent = CastChecked<UCarMovementComponent>(GetVehicleMovement());

#if WITH_EDITOR
    Arrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->ArrowColor = FColor::Yellow;
    Arrow->bTreatAsASprite = true;
    Arrow->SetupAttachment(GetMesh());
    Arrow->bLightAttachment = true;
    Arrow->bIsScreenSizeScaled = true;
#endif
}

float ACarBase::GetMass_Implementation() const
{
    return GetCarMovement()->GetMass();
}

float ACarBase::GetSpeed_Implementation() const
{
    return GetCarMovement()->GetSpeed();
}

float ACarBase::GetSpeedInCM_Implementation() const
{
    return GetCarMovement()->GetSpeed() * UE_M_TO_CM;
}

float ACarBase::GetSpeedInKPH_Implementation() const
{
    return GetCarMovement()->GetSpeed() * 3.6f;
}

float ACarBase::GetSpeedInMPH_Implementation() const
{
    return GetCarMovement()->GetSpeed() * 2.23694f;
}

float ACarBase::GetSpeedInKN_Implementation() const
{
    return GetCarMovement()->GetSpeed() * 1.94384f;
}

FVector ACarBase::GetVelocity_Implementation() const
{
    return GetCarMovement()->GetVelocity() * UE_CM_TO_M;
}

FVector ACarBase::GetAcceleration_Implementation() const
{
    return GetCarMovement()->GetAcceleration() * UE_CM_TO_M;
}

FVector ACarBase::GetVelocityInCM_Implementation() const
{
    return GetCarMovement()->GetVelocity();
}

FVector ACarBase::GetAccelerationInCM_Implementation() const
{
    return GetCarMovement()->GetAcceleration();
}

float ACarBase::IsEngineRunning_Implementation() const
{
    return GetCarMovement()->IsEngineRunning();
}

void ACarBase::StartEngine_Implementation()
{
    GetCarMovement()->SetEngineEnabled(true);
}

void ACarBase::ShutoffEngine_Implementation()
{
    GetCarMovement()->SetEngineEnabled(false);
}