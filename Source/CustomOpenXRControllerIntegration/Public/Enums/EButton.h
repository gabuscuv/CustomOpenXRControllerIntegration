// Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "EButton.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum EButton : uint8
{
    TopButton,
    BottomButton,
    Joystick,
    JoystickClick,
    Trigger,
    Grip,
    JoystickUp,
    JoystickDown,
    JoystickLeft,
    JoystickRight,
    AppMenuButton,
    MAXHIDDEN UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EButton, EButton::MAXHIDDEN);