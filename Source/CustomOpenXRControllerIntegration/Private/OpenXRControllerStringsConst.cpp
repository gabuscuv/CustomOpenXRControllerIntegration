// Copyright 2023 Gabriel Bustillo del Cuvillo

#include "OpenXRControllerStringsConst.h"

FString UOpenXRControllerStringsConst::GetMeshPathString(EBPOpenXRControllerDeviceType DeviceType, FString TrackingSystemName, bool leftController)
{

	/*
		OpenXRExpansion only detect a main type of controller by ecosystem,
		If you need know the type of controller you look up the Name.

		Known Issue: If Oculus/Meta System uses SteamVR as OpenXR Runtime
		will return as "oculus" without model type.

		It's a limitation of SteamVR
	*/
	if (DeviceType == EBPOpenXRControllerDeviceType::DT_OculusTouchController)
	{
		if (TrackingSystemName.Contains("Quest 2"))
		{
			return GetMeshPathString(SubTypeControllersNamesDirectory["TouchV3"], leftController);
		}

		if (TrackingSystemName.Contains("Rift S") || TrackingSystemName.Contains("Quest"))
		{
			return GetMeshPathString(SubTypeControllersNamesDirectory["TouchV2"], leftController);
		}

		return GetMeshPathString(SubTypeControllersNamesDirectory["TouchV1"], leftController);
	}

	if (DeviceType == EBPOpenXRControllerDeviceType::DT_WMRController && TrackingSystemName.Contains("Reverb G2"))
	{
		return GetMeshPathString(SubTypeControllersNamesDirectory["ReverbG2"], leftController);
	}

	// Some controllers only use a type of Mesh because They are symmetricals
	// The main/default behaviour is the controller have a "Left Mesh" and a "Right Mesh"
	switch (DeviceType)
	{
	case EBPOpenXRControllerDeviceType::DT_WMRController:
	case EBPOpenXRControllerDeviceType::DT_ViveController:
	case EBPOpenXRControllerDeviceType::DT_ViveProController:
		return GetMeshPathString(ControllersNamesDirectory[(int)DeviceType], leftController, false);
	default:
		return GetMeshPathString(ControllersNamesDirectory[(int)DeviceType], leftController);
	}
}

FString UOpenXRControllerStringsConst::GetMeshPathString(FString baseName, bool leftController, bool AsymmetricController /*= true by default*/)
{
	/*
		Asymetric Examples:
		'/OpenXR/Devices/OculusTouch_v2(/Left/left_)OculusTouch_v2Controller.left_OculusTouch_v2Controller'
		'/OpenXR/Devices/ValveIndex/Left/left_ValveIndexController.left_ValveIndexController'
		Symetetric Examples:
		/OpenXR/Devices/HTCVive/HTCViveController.HTCViveController'
		/OpenXR/Devices/PicoG2/PicoG2Controller.PicoG2Controller'
	*/
	return MeshBasePath + baseName + "/" + (AsymmetricController ? (IsLeft(leftController) + "/" + IsLeft(leftController).ToLower() + "_") : TEXT("")) + baseName + "Controller." + (AsymmetricController ? IsLeft(leftController).ToLower() + "_" : TEXT("")) + baseName + "Controller";
}

FString UOpenXRControllerStringsConst::GetMaterialInstancePathString(EBPOpenXRControllerDeviceType DeviceType, FString TrackingSystemName, bool leftController)
{
	if (DeviceType == EBPOpenXRControllerDeviceType::DT_OculusTouchController)
	{
		if (TrackingSystemName.Contains("Quest 2"))
		{
			return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["TouchV3"], leftController);
		}

		if (TrackingSystemName.Contains("Rift S") || TrackingSystemName.Contains("Quest"))
		{
			return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["TouchV2"], leftController);
		}

		return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["TouchV1"], leftController);
	}

	if (DeviceType == EBPOpenXRControllerDeviceType::DT_WMRController && TrackingSystemName.Contains("Reverb G2"))
	{
		return GetMaterialInstancePathString(SubTypeControllersNamesDirectory["ReverbG2"], leftController);
	}

	// Some controllers only use only a unique material by Mesh.
	// The main/default behaviour is the controller have a "Left Material" and a "Right Material"
	switch (DeviceType)
	{
	case EBPOpenXRControllerDeviceType::DT_ViveController:
	case EBPOpenXRControllerDeviceType::DT_ViveProController:
		return TEXT(""); // We don't have materials for these..., yet
	case EBPOpenXRControllerDeviceType::DT_WMRController:
		return GetMaterialInstancePathString(ControllersNamesDirectory[(int)DeviceType], leftController, false);
	default:
		return GetMaterialInstancePathString(ControllersNamesDirectory[(int)DeviceType], leftController);
	}
}

FString UOpenXRControllerStringsConst::GetMaterialInstancePathString(FString baseName, bool leftController, bool BiMaterial /*= true by default*/)
{
	return MaterialInstancePath + baseName + "/" + "MI_XRController_" + baseName + (BiMaterial ? "_" + IsLeft(leftController) : TEXT("")) + ".MI_XRController_" + baseName + (BiMaterial ? "_" + IsLeft(leftController) : TEXT(""));
}

FString UOpenXRControllerStringsConst::IsLeft(bool leftController)
{
	return leftController ? "Left" : "Right";
};