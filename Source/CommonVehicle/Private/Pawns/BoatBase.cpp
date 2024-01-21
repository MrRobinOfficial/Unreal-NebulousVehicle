// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Pawns/BoatBase.h"

ABoatBase::ABoatBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}