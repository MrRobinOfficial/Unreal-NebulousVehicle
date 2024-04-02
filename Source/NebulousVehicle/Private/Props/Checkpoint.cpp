// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Props/Checkpoint.h"

#include "Components/SphereComponent.h"
#include "Components/RacerComponent.h"

ACheckpoint::ACheckpoint()
    : Super()
{
    PrimaryActor.bCanEverTick = false;

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision.SetSphereRadius(Radius);
    Collision->bGenerateOverlapEvents = true;
    Collision->SetupAttachment(RootComponent);
    Collision->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
    Collision->bHiddenInGame = false;
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();

    Collision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

void ACheckpoint::OnOverlapBegin(
    UPrimitiveComponent *OverlappedComp,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult &SweepResult)
{
    auto *Racer = OtherActor->FindComponentByClass<URacerComponent>();

    if (!IsValid(Racer))
        return;

    Racer->OnCheckpointReached(GetActorTransform(), Index, bIsLastCheckpoint);
}