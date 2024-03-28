// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Components/CarMovementComponent.h"

UCarMovementComponent::UCarMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCarMovementComponent::SetClutchInput(float Clutch)
{
    RawClutchInput = FMath::Clamp(Clutch, 0.0f, 1.0f);
}

void UCarMovementComponent::IncreaseClutchInput(float ClutchDelta)
{
    RawClutchInput = FMath::Clamp(RawClutchInput + ClutchDelta, 0.f, 1.0f);
}

void UCarMovementComponent::DecreaseClutchInput(float ClutchDelta)
{
    RawClutchInput = FMath::Clamp(RawClutchInput - ClutchDelta, 0.f, 1.0f);
}

void UCarMovementComponent::ToggleEngineState() { /*SetEngineState(!GetEngineState());*/ }

void UCarMovementComponent::SetEngineState(bool bEnabled)
{
    if (bMechanicalSimEnabled == bEnabled)
        return;

	OnEngineStateChanged.Broadcast(bMechanicalSimEnabled, bEnabled);

    bMechanicalSimEnabled = bEnabled;
}

float UCarMovementComponent::GetTorqueFromRPM(float EngineRPM)
{
    return EngineSetup.GetTorqueFromRPM(EngineRPM);
}

void UCarMovementComponent::ClearRawInput()
{
    Super::ClearRawInput();

    RawClutchInput = 0.0f;
}

void UCommonChaosWheeledVehicleSimulation::FillOutputState(FChaosVehicleAsyncOutput& Output)
{
	// #Note: remember to copy/interpolate values from the physics thread output in UChaosVehicleMovementComponent::ParallelUpdate
	const auto& VehicleWheels = PVehicle->Wheels;
	auto& VehicleSuspension = PVehicle->Suspension;

	if (PVehicle->HasTransmission())
	{
		auto& Transmission = PVehicle->GetTransmission();
		Output.VehicleSimOutput.CurrentGear = Transmission.GetCurrentGear();
		Output.VehicleSimOutput.TargetGear = Transmission.GetTargetGear();
		Output.VehicleSimOutput.TransmissionRPM = Transmission.GetTransmissionRPM();

		// TODO: Add clutch support

		Output.VehicleSimOutput.TransmissionTorque = Transmission.GetTransmissionTorque(PVehicle->GetEngine().GetTorqueFromRPM(true));
	}

	if (PVehicle->HasEngine())
	{
		auto& Engine = PVehicle->GetEngine();
		Output.VehicleSimOutput.EngineRPM = Engine.GetEngineRPM();
		Output.VehicleSimOutput.EngineTorque = Engine.GetEngineTorque();
	}

	// #TODO: can we avoid copies when async is turned off
	for (int WheelIdx = 0; WheelIdx < VehicleWheels.Num(); WheelIdx++)
	{
		FWheelsOutput WheelsOut;
		WheelsOut.InContact = VehicleWheels[WheelIdx].InContact();
		WheelsOut.SteeringAngle = VehicleWheels[WheelIdx].GetSteeringAngle();
		WheelsOut.AngularPosition = VehicleWheels[WheelIdx].GetAngularPosition();
		WheelsOut.AngularVelocity = VehicleWheels[WheelIdx].GetAngularVelocity();
		WheelsOut.WheelRadius = VehicleWheels[WheelIdx].GetEffectiveRadius();

		WheelsOut.LateralAdhesiveLimit = VehicleWheels[WheelIdx].LateralAdhesiveLimit;
		WheelsOut.LongitudinalAdhesiveLimit = VehicleWheels[WheelIdx].LongitudinalAdhesiveLimit;

		WheelsOut.bIsSlipping = VehicleWheels[WheelIdx].IsSlipping();
		WheelsOut.SlipMagnitude = VehicleWheels[WheelIdx].GetSlipMagnitude();
		WheelsOut.bIsSkidding = VehicleWheels[WheelIdx].IsSkidding();
		WheelsOut.SkidMagnitude = VehicleWheels[WheelIdx].GetSkidMagnitude();
		WheelsOut.SkidNormal = WheelState.WorldWheelVelocity[WheelIdx].GetSafeNormal();
		WheelsOut.SlipAngle = VehicleWheels[WheelIdx].GetSlipAngle();

		WheelsOut.SuspensionOffset = VehicleSuspension[WheelIdx].GetSuspensionOffset();
		WheelsOut.SpringForce = VehicleSuspension[WheelIdx].GetSuspensionForce();
		WheelsOut.NormalizedSuspensionLength = VehicleSuspension[WheelIdx].GetNormalizedLength();

		WheelsOut.DriveTorque = Chaos::TorqueCmToM(VehicleWheels[WheelIdx].GetDriveTorque());
		WheelsOut.BrakeTorque = Chaos::TorqueCmToM(VehicleWheels[WheelIdx].GetBrakeTorque());

		WheelsOut.bABSActivated = VehicleWheels[WheelIdx].IsABSActivated();
		WheelsOut.bBlockingHit = WheelState.TraceResult[WheelIdx].bBlockingHit;
		WheelsOut.ImpactPoint = WheelState.TraceResult[WheelIdx].ImpactPoint;
		WheelsOut.HitLocation = WheelState.TraceResult[WheelIdx].Location;
		WheelsOut.PhysMaterial = WheelState.TraceResult[WheelIdx].PhysMaterial;

		Output.VehicleSimOutput.Wheels.Add(WheelsOut);
	}
}