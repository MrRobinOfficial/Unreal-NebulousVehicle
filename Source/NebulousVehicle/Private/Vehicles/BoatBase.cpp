// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/BoatBase.h"

// Camera & SpringArm
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

FName ABoatBase::SpringArmComponentName(TEXT("SpringArm"));
FName ABoatBase::CameraComponentName(TEXT("Camera"));
FName ABoatBase::VehicleMeshComponentName(TEXT("VehicleMesh"));

ABoatBase::ABoatBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleMeshComponentName);
	Mesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	Mesh->BodyInstance.bSimulatePhysics = false;
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;
	Mesh->BodyInstance.bUseCCD = true;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCanEverAffectNavigation(false);
	RootComponent = Mesh;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SpringArm = CreateOptionalDefaultSubobject<USpringArmComponent>(SpringArmComponentName);

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;

	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateOptionalDefaultSubobject<UCameraComponent>(CameraComponentName);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}