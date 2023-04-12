// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenXRController.h"
#include "Kismet/KismetSystemLibrary.h" 
//#include "UMagicEnum_.h"
#include "MagicEnum/magic_enum.hpp"
#include <string>

// Sets default values
AOpenXRController::AOpenXRController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpringArm"));
	StaticMeshController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));

}
FString AOpenXRController::IsLeft()
	{
		// Unique usecase
//		if(DeviceType == EBPOpenXRControllerDeviceType::DT_WMRController && ! TrackingSystemName.Contains("Reverb G2")) {return "";}
  		return isLeftController ? "Left" : "Right";
	};
// Called when the game starts or when spawned
void AOpenXRController::BeginPlay()
{
	Super::BeginPlay();
	#if WITH_EDITORONLY_DATA
		if (isSpoffingController && ! UKismetSystemLibrary::IsPackagedForDistribution()){SetMesh();return;}
	#endif
	
	do
	{
		//if (Result == EBPXRResultSwitch::OnFailed){/*Delay*/}
		UOpenXRExpansionFunctionLibrary::GetXRMotionControllerType(TrackingSystemName,DeviceType,Result);
	}
	while(Result != EBPXRResultSwitch::OnSucceeded);
	SetMesh();
}

void AOpenXRController::SetMesh()
{
	StaticMeshController->SetStaticMesh((UStaticMesh*)StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *GetMeshPathString(DeviceType) , nullptr, LOAD_None, nullptr));
	StaticMeshController->CreateDynamicMaterialInstance(0,(UMaterialInstance*)StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, *GetMaterialInstancePathString(DeviceType) , nullptr, LOAD_None, nullptr));
}

void AOpenXRController::HighlightButtons_Implementation(EButton button, bool state)
{
	
	StaticMeshController->SetScalarParameterValueOnMaterials(
//		UMagicEnumHelper::EnumToFName<EButton>(button)
		FName(FString(std::string(magic_enum::enum_name<EButton>(button)).c_str())), 
		(float)(! state)
		);
}

void AOpenXRController::ClearAllHighlightButtons_Implementation()
{
	return;
}

FString AOpenXRController::GetMeshPathString(EBPOpenXRControllerDeviceType Name)
{
	if( DeviceType == EBPOpenXRControllerDeviceType::DT_OculusTouchController)
	{
		if (TrackingSystemName.Contains("Quest 2"))
		{
			return GetMeshPathString(SubTypeControllersNamesDirectory["TouchV3"]);
		}

		if (TrackingSystemName.Contains("Rift S") || TrackingSystemName.Contains("Quest"))
		{
			return GetMeshPathString(SubTypeControllersNamesDirectory["TouchV2"]);
		}
		
		return GetMeshPathString(SubTypeControllersNamesDirectory["TouchV1"]);
	}

	if( DeviceType == EBPOpenXRControllerDeviceType::DT_WMRController && TrackingSystemName.Contains("Reverb G2"))
	{
		return GetMeshPathString(SubTypeControllersNamesDirectory["ReverbG2"]);
	}

	return GetMeshPathString(ControllersNamesDirectory[(int)Name]);
}

FString AOpenXRController::GetMeshPathString(FString baseName)
{
		return MeshBasePath + baseName + "/" + IsLeft() + "/" + IsLeft().ToLower()  + "_" + baseName + "Controller." + IsLeft().ToLower()  + "_" + baseName + "Controller";
}

FString AOpenXRController::GetMaterialInstancePathString(EBPOpenXRControllerDeviceType Name)
{
	if( DeviceType == EBPOpenXRControllerDeviceType::DT_OculusTouchController)
	{
		if (TrackingSystemName.Contains("Quest 2"))
		{
			return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["TouchV3"]);
		}

		if (TrackingSystemName.Contains("Rift S") || TrackingSystemName.Contains("Quest"))
		{
			return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["TouchV2"]);
		}
		
		return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["TouchV1"]);
	}

	if( DeviceType == EBPOpenXRControllerDeviceType::DT_WMRController && TrackingSystemName.Contains("Reverb G2"))
	{
		return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["ReverbG2"]);
	}

	return GetMaterialInstancePathString(ControllersNamesDirectory[(int)Name]);
}


// (/CustomOpenXRControllerIntegration/Materials/) ValveIndex/M_XRController_ValveIndex_Left.M_XRController_ValveIndex_Left'
FString AOpenXRController::GetMaterialInstancePathString(FString baseName)
{
	//FIXME: This will make Issues with EBPOpenXRControllerDeviceType::DT_WMRController and not Reverb G2, because It only have one unique material
		return MaterialInstancePath + baseName + "/" + "MI_XRController_" + baseName + "_" + IsLeft() + ".MI_XRController_" + baseName + "_" + IsLeft();
}

