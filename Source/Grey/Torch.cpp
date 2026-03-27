// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch.h"
#include "AnimationType.h"

ATorch::ATorch()
{
    PrimaryActorTick.bCanEverTick = true;

    ItemName = FText::FromString("Torch");
    AnimationType = EAnimationType::Torch;

    TorchLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("TorchLight"));
    TorchLight->SetupAttachment(RootComponent);

    TorchLight->Intensity = 15000.f;
    TorchLight->AttenuationRadius = 2000.f;
    TorchLight->InnerConeAngle = 10.f;
    TorchLight->OuterConeAngle = 35.f;
    TorchLight->SourceRadius = 1.f;
    TorchLight->SoftSourceRadius = 1.f;

    bIsLit = true;
}


void ATorch::BeginPlay()
{
    LightIntensity = TorchLight->Intensity;
        
}

void ATorch::Uequip()
{
    Super::Uequip();

    ATorch::TurnOff();
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
    TorchLight->SetVisibility(true);
    TorchLight->Intensity = LightIntensity;
    bIsLit = true;
   
}

void ATorch::TurnOff()
{
    TorchLight->SetVisibility(false);
    TorchLight->Intensity = 0.f;
    bIsLit = false;
   
}

void ATorch::UseItem()
{
    ToggleTorch();
}


