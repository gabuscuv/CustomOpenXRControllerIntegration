// Copyright 2023 Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/IOpenXRController.h"
#include "OpenXRExpansionTypes.h"
#include "OpenXRExpansionFunctionLibrary.h"
#include "Enums/EButton.h"

#include "OpenXRController.generated.h"

UCLASS()
class CUSTOMOPENXRCONTROLLERINTEGRATION_API AOpenXRController : public AActor, public IOpenXRControllerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOpenXRController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isLeftController = true;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent *StaticMeshController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TrackingSystemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBPOpenXRControllerDeviceType DeviceType;
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSpoffingController = false;
#endif

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OpenXRController")
	void HighlightButtons(EButton button, bool state, bool AddOffset);
	virtual void HighlightButtons_Implementation(EButton button, bool state, bool AddOffset) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OpenXRController")
	void ClearAllHighlightButtons();
	virtual void ClearAllHighlightButtons_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	EBPXRResultSwitch Result = EBPXRResultSwitch::OnSucceeded;

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

	void SetMesh();
	static FString GetMeshPathString(EBPOpenXRControllerDeviceType Name, FString TrackingSystemName, bool leftController);
	static FString GetMeshPathString(FString baseName, bool leftController, bool AsymmetricController = true);
	static FString GetMaterialInstancePathString(EBPOpenXRControllerDeviceType Name, FString TrackingSystemName, bool leftController);
	static FString GetMaterialInstancePathString(FString baseName, bool leftController, bool BiMaterial = true);
	static FString IsLeft(bool IsLeftController);
};
