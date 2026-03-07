// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "Components/SpotLightComponent.h"
#include "Torch.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API ATorch : public APlayerItem
{
	GENERATED_BODY()
	
	ATorch();

protected:
    
    UPROPERTY(EditAnywhere)
    USpotLightComponent* TorchLight;

    UPROPERTY(EditAnywhere)
    bool bIsLit;

    UPROPERTY(EditAnywhere)
    float LightIntensity = 10000.f;

public:
    UFUNCTION(BlueprintCallable)
    void ToggleTorch();

    UFUNCTION(BlueprintCallable)
    void TurnOn();

    UFUNCTION(BlueprintCallable)
    void TurnOff();
};
