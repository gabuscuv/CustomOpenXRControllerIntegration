// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "Enums/EActionButtons.h"
#include "OpenXRControllerChildActor.generated.h"

/**
 *
 */
UCLASS()
class CUSTOMOPENXRCONTROLLERINTEGRATION_API UOpenXRControllerChildActor : public UChildActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float HeldTimerDuration;

private:
	FTimerHandle HeldTimerHandle;
	bool isLeft = false;
	bool isStillHeldHand = false;

public:
	UFUNCTION(BlueprintCallable)
	void ShowControllerAndHighlightButtons(EActionButtons button, bool lefthanded);
	UFUNCTION(BlueprintCallable)
	void ShouldShowController(bool left, AActor *actor);

private:
	void shouldShowController_TimerElapsed();
};
