// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Components/RacerComponent.h"

void URacerComponent::OnCheckpointReached(
    const FTransform &NewTransform,
    const int32 &NewIndex,
    const bool bIsLastCheckpoint)
{
    if (CheckpointIndex == NewIndex)
        return;

    CheckpointTransform = NewTransform;
    CheckpointIndex = NewIndex;

    if (bIsLastCheckpoint)
    {
        LapIndex++;
    }
}

void URacerComponent::Respawn()
{
    // Respawn logic
}

float URacerComponent::CalcScore() const
{
    const FVector &OwnerLocation = GetOwner()->GetActorLocation();
    return LapIndex + CheckpointIndex + FVector::DistSquared(CheckpointTransform, OwnerLocation);
}