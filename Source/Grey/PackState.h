#pragma once

#include "CoreMinimal.h"
#include "PackState.generated.h"

UENUM(BlueprintType)
enum class EPackState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Patrolling  UMETA(DisplayName = "Patrolling"),
    Hunting     UMETA(DisplayName = "Hunting"),
    Attacking   UMETA(DisplayName = "Attacking")
};