// Copyright 2023 Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/IOpenXRController.h"
#include "OpenXRExpansionTypes.h"
#include "OpenXRExpansionFunctionLibrary.h"
#include "OpenXRController.generated.h"

//forward declaration
enum EButton : uint8;

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
	FName GetEnumName(EButton button);

	void SetMesh();

};
