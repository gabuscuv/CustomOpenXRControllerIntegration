// Copyright 2023 Gabriel Bustillo del Cuvillo

#include "OpenXRController.h"
#include "Kismet/KismetSystemLibrary.h"

#include <string>

#include "MagicEnum/magic_enum.hpp"
#include "OpenXRControllerStringsConst.h"

// Sets default values
AOpenXRController::AOpenXRController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpringArm"));
	StaticMeshController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));

	StaticMeshController->SetStaticMesh((UStaticMesh *)StaticLoadObject(
		UStaticMesh::StaticClass(), nullptr,
		*UOpenXRControllerStringsConst::GetMeshPathString(
			EBPOpenXRControllerDeviceType::DT_OculusTouchController, TEXT("Rift S"), isLeftController),
		nullptr, LOAD_None, nullptr));
}

// Called when the game starts or when spawned
void AOpenXRController::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITORONLY_DATA
	if (isSpoffingController && !UKismetSystemLibrary::IsPackagedForDistribution())
	{
		SetMesh();
		return;
	}
#endif
	size_t counter = 0, attempts = 3;
	do
	{
		// if (Result == EBPXRResultSwitch::OnFailed){/*Delay*/}
		UOpenXRExpansionFunctionLibrary::GetXRMotionControllerType(TrackingSystemName, DeviceType, Result);
		counter++;
	} while (Result != EBPXRResultSwitch::OnSucceeded || counter > attempts);
	if (Result != EBPXRResultSwitch::OnSucceeded)
	{
		UE_LOG(LogTemp, Error, TEXT("OPENXRCONTROLLER: ERROR, It doesn't Found OpenXRController"))
		return;
	}
	SetMesh();
}

void AOpenXRController::SetMesh()
{
	StaticMeshController->SetStaticMesh((UStaticMesh *)StaticLoadObject(UStaticMesh::StaticClass(), nullptr,
																		*UOpenXRControllerStringsConst::GetMeshPathString(
																			DeviceType, TrackingSystemName, isLeftController),
																		nullptr, LOAD_None, nullptr));

	StaticMeshController->CreateDynamicMaterialInstance(0, (UMaterialInstance *)StaticLoadObject(
															   UMaterialInstance::StaticClass(), nullptr,
															   *UOpenXRControllerStringsConst::GetMaterialInstancePathString(
																   DeviceType, TrackingSystemName, isLeftController),
															   nullptr, LOAD_None, nullptr));
}

void AOpenXRController::HighlightButtons_Implementation(EButton button, bool state, bool AddOffset)
{
	StaticMeshController->SetScalarParameterValueOnMaterials(
		//		UMagicEnumHelper::EnumToFName<EButton>(button)
		FName(FString(std::string(magic_enum::enum_name<EButton>(button)).c_str())),
		(float)(!state));
}

void AOpenXRController::ClearAllHighlightButtons_Implementation()
{
	return;
}
