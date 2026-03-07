// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch.h"

ATorch::ATorch()
{
    PrimaryActorTick.bCanEverTick = false;

    ItemName = FText::FromString("Torch");

    TorchLight = CreateDefaultSubobject<USpotLightComponent>("TorchLight");
    TorchLight->SetupAttachment(RootComponent);

    TorchLight->Intensity = 0.f;
    TorchLight->AttenuationRadius = 3000.f;
    TorchLight->InnerConeAngle = 10.f;
    TorchLight->OuterConeAngle = 35.f;
    TorchLight->SourceRadius = 1.f;
    TorchLight->SoftSourceRadius = 1.f;

    bIsLit = false;
}

void ATorch::ToggleTorch()
{
    if (bIsLit)
    {
        TurnOff();
    }
    else
    {
        TurnOn();
    }
}

void ATorch::TurnOn()
{
    TorchLight->Intensity = LightIntensity;
    bIsLit = true;
}

void ATorch::TurnOff()
{
    TorchLight->Intensity = 0.f;
    bIsLit = false;
}
