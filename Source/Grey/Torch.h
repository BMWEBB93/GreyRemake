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
	
public:

	ATorch();

protected:
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USpotLightComponent* TorchLight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bIsLit;

    UPROPERTY(EditAnywhere)
    float LightIntensity = 20000.f;

public:
    UFUNCTION(BlueprintCallable)
    void ToggleTorch();

    UFUNCTION(BlueprintCallable)
    void TurnOn();

    UFUNCTION(BlueprintCallable)
    void TurnOff();

    UFUNCTION(BlueprintCallable)
    virtual void UseItem() override;
    virtual void BeginPlay() override;

    virtual void Uequip();
};
