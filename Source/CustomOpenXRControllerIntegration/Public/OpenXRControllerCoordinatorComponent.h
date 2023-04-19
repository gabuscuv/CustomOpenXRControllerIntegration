// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "Enums/EActionButtons.h"
#include "InputCoreTypes.h"
#include "OpenXRControllerCoordinatorComponent.generated.h"

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUSTOMOPENXRCONTROLLERINTEGRATION_API UOpenXRControllerCoordinatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float HeldTimerDuration = 0.5f;
	UPROPERTY(EditAnywhere)
	FString LeftControllerComponentName = "OculusLeftController";
	UPROPERTY(EditAnywhere)
	FString RightControllerComponentName = "OculusRightController";


private:
	FTimerHandle HeldTimerHandle;
	UChildActorComponent* LeftController;
	UChildActorComponent* RightController;
	bool isLeft = false;
	bool isStillHeldHand = false;

public:
	UFUNCTION(BlueprintCallable)
	void ShowControllerAndHighlightButtons(EActionButtons button, bool lefthanded);
	UFUNCTION(BlueprintCallable)
	void ShouldShowController(bool left, UObject *object);
	UFUNCTION(BlueprintCallable)
	void HideControllerVisibility();
	UFUNCTION(BlueprintCallable)
	void EndsOverlappingObject();

protected:
	virtual void BeginPlay() override;

private:
	UChildActorComponent* GetChildActorComponent(bool bRightDominantHand);
	AActor* GetChildActor(bool bRightDominantHand);
	void shouldShowController_TimerElapsed();
};
