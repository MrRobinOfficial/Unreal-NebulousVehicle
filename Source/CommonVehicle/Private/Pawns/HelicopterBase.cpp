// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/HelicopterBase.h"

AHelicopterBase::AHelicopterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}