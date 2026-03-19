// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPackAttack : uint8
{
    None        UMETA(DisplayName = "None"),
    Flee        UMETA(DisplayName = "Flee"),
    Surround  UMETA(DisplayName = "Surround"),
    Attack     UMETA(DisplayName = "Attack"),
};
