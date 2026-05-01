// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildableObjects.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "NiagaraComponent.h"


#include "CampFire.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API ACampFire : public ABuildableObjects
{
	GENERATED_BODY()

public:
	ACampFire();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldStartLit = false;

	UPROPERTY()
	UNiagaraComponent* FireComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundAttenuation* FireAttenuation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPointLightComponent* FireLight;

	float FireLightMaxIntensity = 5000.f;

	float Volume = 0.2f;
	float Pitch = 1.f;
	bool bIsLit = false;

	virtual void Tick(float DeltaTime);
	virtual void BeginPlay();
	void HandlePlayerPlacement();

	void StartFire();

};
