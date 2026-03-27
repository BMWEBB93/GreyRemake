// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_StartFire.h"

#include "PlayerCharacter.h"

void UAnimNotify_StartFire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;


    APlayerCharacter* Char = Cast<APlayerCharacter>(Owner);
    if (Char)
    {
        if (Char->FireToLight && Char->bCanLightFire)
            Char->FireToLight->StartFire();
    }
}
