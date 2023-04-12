// Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "EButton.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EButton : uint8
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
    AppMenuButton
};
