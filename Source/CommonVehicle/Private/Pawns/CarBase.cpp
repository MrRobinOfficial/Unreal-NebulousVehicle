// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/CarBase.h"

#include "Components/ArrowComponent.h"
#include "Components/CommonVehicleMovementComponent.h"

ACarBase::ACarBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCommonVehicleMovementComponent>(AWheeledVehiclePawn::VehicleMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    CommonVehicleMovementComponent = CastChecked<UCommonVehicleMovementComponent>(GetVehicleMovement());

#if WITH_EDITOR
    Arrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->ArrowColor = FColor::Yellow;
    Arrow->bTreatAsASprite = true;
    Arrow->SetupAttachment(GetMesh());
    Arrow->bLightAttachment = true;
    Arrow->bIsScreenSizeScaled = true;
#endif
}