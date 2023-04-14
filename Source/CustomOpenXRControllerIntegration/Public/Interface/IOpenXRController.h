// Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IOpenXRController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOpenXRControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class CUSTOMOPENXRCONTROLLERINTEGRATION_API IOpenXRControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OpenXRController")
	void HighlightButtons(EButton button, bool state, bool AddOffset);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OpenXRController")
	void ClearAllHighlightButtons();
};
