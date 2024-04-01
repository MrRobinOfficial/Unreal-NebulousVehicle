// Copyright 2023-2024 MrRobin. All Rights Reserved.

// NebulousVehicle
#include "Vehicles/CarArcade.h"

#include "Libraries/ArcadeLibrary.h"
//#include "Components/CarMovementComponent.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include "Components/LightComponent.h"

// EnhancedInput
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

// Niagara
#include "NiagaraEmitter.h"

ACarArcade::ACarArcade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // ObjectInitializer.DoNotCreateDefaultSubobject(CameraComponentName).DoNotCreateDefaultSubobject(SpringArmComponentName)
{

}

void ACarArcade::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(HeadlightAction, ETriggerEvent::Triggered, this, &ACarArcade::Input_OnHeadlight);
		EnhancedInputComponent->BindAction(HonkAction, ETriggerEvent::Triggered, this, &ACarArcade::Input_OnHonk);
	}
}

void ACarArcade::NotifyControllerChanged()
{
	if (auto* PreviousPlayer = Cast<APlayerController>(PreviousController))
	{
		if (auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PreviousPlayer->GetLocalPlayer()))
		{
			InputSubsystem->RemoveMappingContext(ArcadeInputMappingContext);
		}
	}

	if (auto* NewPlayer = Cast<APlayerController>(GetController()))
	{
		NewPlayer->InputYawScale_DEPRECATED = 1.0f;
		NewPlayer->InputPitchScale_DEPRECATED = 1.0f;
		NewPlayer->InputRollScale_DEPRECATED = 1.0f;

		if (auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayer->GetLocalPlayer()))
		{
			FModifyContextOptions Options;
			Options.bNotifyUserSettings = true;

			InputSubsystem->AddMappingContext(ArcadeInputMappingContext, 1, Options);
		}
	}

	Super::NotifyControllerChanged();
}

void ACarArcade::SetHeadlightState(EHeadlightState NewState)
{
	if (HeadlightState == NewState)
		return;

	OnHeadlightChanged.Broadcast(HeadlightState, NewState);

	switch (NewState)
	{
		case EHeadlightState::Off:
			UArcadeLibrary::SetActiveForLights(Headlights.Data.Lights, false);
			break;

		case EHeadlightState::LowBeam:
			UArcadeLibrary::SetActiveForLights(Headlights.Data.Lights, true);
			UArcadeLibrary::SetIntensityForLights(Headlights.Data.Lights, Headlights.LowIntensity);
			break;

		case EHeadlightState::HighBeam:
			UArcadeLibrary::SetIntensityForLights(Headlights.Data.Lights, Headlights.HighIntensity);
			break;
	}

	HeadlightState = NewState;
}

#pragma region Input Functions
void ACarArcade::SetBrakeInput_Implementation(float AxisValue)
{
	Super::SetBrakeInput_Implementation(AxisValue);

	const float Intensity = Taillights.Intensity * AxisValue;
	UArcadeLibrary::SetIntensityForLights(Taillights.Data.Lights, Intensity);
}
#pragma endregion

void ACarArcade::Input_OnHeadlight(const FInputActionValue& Value)
{
	switch (HeadlightState)
	{
		case EHeadlightState::Off:
			SetHeadlightState(EHeadlightState::LowBeam);
			break;

		case EHeadlightState::LowBeam:
			SetHeadlightState(EHeadlightState::HighBeam);
			break;

		case EHeadlightState::HighBeam:
			SetHeadlightState(EHeadlightState::Off);
			break;
	}
}

void ACarArcade::Input_OnHonk(const FInputActionValue& Value)
{
	// Honk
}
#pragma endregion