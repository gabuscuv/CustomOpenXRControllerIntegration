// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenXRControllerChildActor.h"
#include "TimerManager.h"

#include "Enums/EButton.h"
#include "VRGripInterface.h"
#include "Interface/IOpenXRController.h"

void UOpenXRControllerChildActor::ShowControllerAndHighlightButtons(EActionButtons button, bool lefthanded)
{

    switch (button)
    {
    case EActionButtons::Grip:
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(), EButton::Grip, !lefthanded, true);
        break;
    case EActionButtons::Movement:
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(), EButton::Joystick, !lefthanded, false);
        break;
    case EActionButtons::OpenHolograph:
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(), EButton::TopButton, !lefthanded, false);
        break;
    case EActionButtons::OpenGameSystemMenu:
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(), EButton::BottomButton, !lefthanded, false);
        break;

    default:
        break;
    }
}

void UOpenXRControllerChildActor::ShouldShowController(bool left, AActor *actor)
{
    if (!actor->GetClass()->ImplementsInterface(UVRGripInterface::StaticClass())){return;}
    bool isHeld;
    TArray<FBPGripPair> uselessData;
    IVRGripInterface::Execute_IsHeld(actor, uselessData, isHeld);
    if (!isHeld){return;}

    isStillHeldHand = isHeld;
    GetOwner()->GetWorldTimerManager().SetTimer(HeldTimerHandle, this, &UOpenXRControllerChildActor::shouldShowController_TimerElapsed, HeldTimerDuration, false);
}

void UOpenXRControllerChildActor::shouldShowController_TimerElapsed()
{
    if (!isStillHeldHand){return;}

    ShowControllerAndHighlightButtons(EActionButtons::Grip, isLeft);
}