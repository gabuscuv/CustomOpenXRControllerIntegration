// Copyright 2023 Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "OpenXRControllerStringsConst.generated.h"

USTRUCT()
struct CUSTOMOPENXRCONTROLLERINTEGRATION_API FOpenXRControllerStringsConst
{
    GENERATED_BODY()
private:    
    static const inline FString MeshBasePath = "/OpenXR/Devices/";
	static const inline FString MaterialInstancePath = "/CustomOpenXRControllerIntegration/Materials/";

	static const inline TMap<int, FString> ControllersNamesDirectory = {
		{(int)EBPOpenXRControllerDeviceType::DT_ValveIndexController, "ValveIndex"},
		{(int)EBPOpenXRControllerDeviceType::DT_ViveController, "HTCVive"},
		{(int)EBPOpenXRControllerDeviceType::DT_WMRController, "MicrosoftMixedReality"},
	};

	static const inline TMap<FString, FString> SubTypeControllersNamesDirectory = {
		{"TouchV1", "OculusTouch"},
		{"TouchV2", "OculusTouch_v2"},
		{"TouchV3", "OculusTouch_v3"},
		{"TouchPro", "OculusTouch_v3"},
		{"ReverbG2", "HPMixedReality"},
	};

public:
    static FString GetMeshPathString(EBPOpenXRControllerDeviceType Name, FString TrackingSystemName, bool leftController);
	static FString GetMaterialInstancePathString(EBPOpenXRControllerDeviceType Name, FString TrackingSystemName, bool leftController);

private:
    static FString GetMeshPathString(FString baseName, bool leftController, bool AsymmetricController = true);
    static FString GetMaterialInstancePathString(FString baseName, bool leftController, bool BiMaterial = true);
	static FString IsLeft(bool IsLeftController);
};