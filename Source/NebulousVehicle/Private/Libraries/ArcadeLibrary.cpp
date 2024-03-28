// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Libraries/ArcadeLibrary.h"

#include "Components/LightComponent.h"

void UArcadeLibrary::SetIntensityForLights(
    const TArray<ULightComponent*> Lights,
    float NewIntensity)
{
    for (ULightComponent* Light : Lights)
        Light->SetIntensity(NewIntensity);
}

void UArcadeLibrary::SetActiveForLights(
    const TArray<ULightComponent*> Lights,
    bool bNewActive,
    bool bReset)
{
    for (ULightComponent* Light : Lights)
        Light->SetActive(bNewActive, bReset);
}