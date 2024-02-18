// Gabriel Bustillo del Cuvillo

#pragma once

#include "CoreMinimal.h"
#include "EActionButtons.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EActionButtons : uint8
{
    OpenInGameMenu,
    OpenGameSystemMenu,
    Movement,
    Grip,
    Select
};
