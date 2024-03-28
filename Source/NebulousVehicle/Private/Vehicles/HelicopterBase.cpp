// Copyright 2023-2024 MrRobin. All Rights Reserved.

#include "Vehicles/HelicopterBase.h"

// Camera & SpringArm
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

FName AHelicopterBase::SpringArmComponentName(TEXT("SpringArm"));
FName AHelicopterBase::CameraComponentName(TEXT("Camera"));
FName AHelicopterBase::VehicleMeshComponentName(TEXT("VehicleMesh"));

AHelicopterBase::AHelicopterBase(const FObjectInitializer& ObjectInitializer)
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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(SpringArmComponentName);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;

	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateDefaultSubobject<UCameraComponent>(CameraComponentName);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}