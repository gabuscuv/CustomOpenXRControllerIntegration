// Copyright 2023 Gabriel Bustillo del Cuvillo

#include "OpenXRControllerCoordinatorComponent.h"
#include "TimerManager.h"

#include "Enums/EButton.h"
#include "VRGripInterface.h"
#include "Interface/IOpenXRController.h"
UOpenXRControllerCoordinatorComponent::UOpenXRControllerCoordinatorComponent()
{
	bWantsInitializeComponent = true;
}

void UOpenXRControllerCoordinatorComponent::InitializeComponent()
{
    TArray<UChildActorComponent*> ChildActorArray;
    GetOwner()->GetComponents<UChildActorComponent*>(ChildActorArray);
    for (auto component : ChildActorArray)
    {
        if (component->GetName().Equals(LeftControllerComponentName))
        {
            LeftController = component;
        }

        if (component->GetName().Equals(RightControllerComponentName))
        {
            RightController = component;
        }

        if(LeftController && RightController ){break;}
    }

        if(!LeftController){UE_LOG(LogTemp, Warning, TEXT("WARNING: It doesn't found the Left Controller"));;}
        if(!RightController){UE_LOG(LogTemp, Warning, TEXT("WARNING: It doesn't found the Right Controller"));;}

    }

void UOpenXRControllerCoordinatorComponent::ShowControllerAndHighlightButtons(EActionButtons button, bool lefthanded)
{
    this->GetChildActorComponent(lefthanded)->SetVisibility(true,true);
    switch (button)
    {
        // AnyHand
    case EActionButtons::Grip:
        
        IOpenXRControllerInterface::Execute_SetText(this->GetChildActor(lefthanded), FText::FromStringTable(FName("OXRControllerLocTable"), TEXT("Grip")));
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(lefthanded), EButton::Grip, true, true);
        break;
    // Left Hand in Right Handed (viceversa for Left Handed)
    case EActionButtons::Movement:
        IOpenXRControllerInterface::Execute_SetText(this->GetChildActor(lefthanded), FText::FromStringTable(FName("OXRControllerLocTable"), TEXT("Movement")));
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(!lefthanded), EButton::Joystick, true, false);
        break;
    // Left Hand in Right Handed (viceversa for Left Handed)
    case EActionButtons::OpenInGameMenu:
        IOpenXRControllerInterface::Execute_SetText(this->GetChildActor(lefthanded), FText::FromStringTable(FName("OXRControllerLocTable"), TEXT("OpenInGameMenu")));
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(!lefthanded), EButton::TopButton, true, false);
        break;
    // Left Hand in Right Handed (viceversa for Left Handed)
    case EActionButtons::OpenGameSystemMenu:
        IOpenXRControllerInterface::Execute_SetText(this->GetChildActor(lefthanded), FText::FromStringTable(FName("OXRControllerLocTable"), TEXT("OpenGameMenu")));
        IOpenXRControllerInterface::Execute_HighlightButtons(this->GetChildActor(!lefthanded), EButton::BottomButton, true, false);
        break;

    default:
        break;
    }
}

void UOpenXRControllerCoordinatorComponent::ShouldShowController(bool left, UObject * object)
{
    if (!object->GetClass()->ImplementsInterface(UVRGripInterface::StaticClass())){return;}
    bool isHeld;
    TArray<FBPGripPair> uselessData;
    IVRGripInterface::Execute_IsHeld(object, uselessData, isHeld);
    if (!isHeld){return;}
 
    isStillHeldHand = isHeld;
    GetOwner()->GetWorldTimerManager().SetTimer(HeldTimerHandle, this, &UOpenXRControllerCoordinatorComponent::shouldShowController_TimerElapsed, HeldTimerDuration, false);
}

void UOpenXRControllerCoordinatorComponent::HideControllerVisibility()
{
    if (!LeftController->GetVisibleFlag() || !RightController->GetVisibleFlag()){return;}

    LeftController->SetVisibility(false,true);
    RightController->SetVisibility(false,true);
}

void UOpenXRControllerCoordinatorComponent::EndsOverlappingObject()
{
    isStillHeldHand = false;
    HideControllerVisibility();
}

void UOpenXRControllerCoordinatorComponent::shouldShowController_TimerElapsed()
{
    if (!isStillHeldHand){return;}

    ShowControllerAndHighlightButtons(EActionButtons::Grip, isLeft);
}


AActor *UOpenXRControllerCoordinatorComponent::GetChildActor(bool bRightDominantHand)
{
    return GetChildActorComponent(bRightDominantHand)->GetChildActor();
}

UChildActorComponent *UOpenXRControllerCoordinatorComponent::GetChildActorComponent(bool bRightDominantHand)
{
    return bRightDominantHand ? LeftController : RightController;
}