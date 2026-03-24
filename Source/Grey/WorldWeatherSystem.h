// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"

#include "Components/ExponentialHeightFogComponent.h"
#include "Components/DirectionalLightComponent.h"

#include "Subsystems/WorldSubsystem.h"
#include "WorldWeatherSystem.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UWorldWeatherSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public: 

	virtual void Tick(float DeltaTime) override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void FindDaySequence();

	virtual TStatId GetStatId() const override;

	virtual bool IsTickable() const override
	{
		return true;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDirectionalLightComponent* Sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UExponentialHeightFogComponent* Fog;

	float MaxFogDensity = .8f;

};
