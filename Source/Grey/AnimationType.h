// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAnimationType : uint8
{
    Torch        UMETA(DisplayName = "Torch"),
    Axe  UMETA(DisplayName = "Axe"),
    Bag  UMETA(DisplayName = "Bag"),
    Radio  UMETA(DisplayName = "Radio"),


};