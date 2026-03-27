// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"

#include "BuildableObjects.h"

#include "TentBuilt.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API ATentBuilt : public ABuildableObjects
{
	GENERATED_BODY()
	

public:

	ATentBuilt();
	virtual void Tick(float DeltaTime);

};
