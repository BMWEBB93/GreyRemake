// Fill out your copyright notice in the Description page of Project Settings.


#include "Lighter.h"
#include "PlayerCharacter.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ALighter::ALighter()
{
    PrimaryActorTick.bCanEverTick = true;

    ItemName = FText::FromString("Lighter");
    AnimationType = EAnimationType::Radio;

    LighterCap = CreateDefaultSubobject<UStaticMeshComponent>("LighterCap");
    LighterCap->SetupAttachment(ItemMesh);
    LighterCap->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Turn off collision
    LighterCap->SetSimulatePhysics(false);    // Turn off physics
    LighterCap->SetEnableGravity(false);      // Turn off gravity 

    LighterCap->SetRelativeRotation(FRotator(180.f, 0.f, 180.f));
    LighterCap->SetRelativeLocation(FVector(0.f, 4.35f, 6.12f));

    LighterCap->SetVisibility(true);


    Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
    Light->AttachToComponent(
        ItemMesh,
        FAttachmentTransformRules::SnapToTargetNotIncludingScale,
        TEXT("FlameSocket")
    );

    Light->Intensity = 0.f;
    Light->AttenuationRadius = 150.f;
    Light->SourceRadius = 1.5f;
    Light->SoftSourceRadius = 1.f;
}

void ALighter::UseItem()
{
    if (bIsLit)
    {
        if (Player->FireToLight != NULL && Player->bCanLightFire)
        {
            if (LightFireMontage)
            {
                // Get the owner of the torch
                ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
                if (!OwnerCharacter) return;

                // Get the AnimInstance
                UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
                if (!AnimInstance) return;

                AnimInstance->Montage_Play(LightFireMontage, 1.0f);

            }
        }

        else
        {
            LighterCap->SetRelativeRotation(FRotator(180.f, 0.f, 180.f));
            bIsLit = false;

            if (FlameComponent)
            {
                FlameComponent->Deactivate();
                Light->SetIntensity(0.f);
            }
        }
        
    }
    else
    {
        LighterCap->SetRelativeRotation(FRotator(180.f, 0.f, 80.f));
        bIsLit = true;
        Light->SetIntensity(LightMaxIntensity);


        if (!FlameComponent)
        {
            FlameComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
                Flame,
                ItemMesh,
                FName("FlameSocket"),
                FVector::ZeroVector,
                FRotator::ZeroRotator,
                EAttachLocation::SnapToTarget,
                false);
        }
        else
        {
            FlameComponent->Activate();
        }

       
    }
}

void ALighter::Equip()
{
    Super::Equip();

    // Correct the rotation/position to fit in  the hand


    SetActorRelativeRotation(FRotator(180.f, 270.f, 90.f));
    SetActorRelativeLocation(FVector(-15.f, 0.f, 0.f));

    LighterCap->SetVisibility(true);

}

void ALighter::Uequip()
{
    if (bIsLit)
    {
        UseItem();
    }

    LighterCap->SetVisibility(false);


    Super::Uequip();
}

void ALighter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Light && bIsLit)
    {
        float Time = GetWorld()->GetTimeSeconds();

        float Flicker = FMath::Sin(Time * 8.f) * 50.f;         
        Flicker += FMath::FRandRange(-20.f, 20.f);             

        Light->SetIntensity(400.f + Flicker);
    }
}
