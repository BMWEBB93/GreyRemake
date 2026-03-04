// Fill out your copyright notice in the Description page of Project Settings.

#include "Wolf.h"
#include "PlayerCharacter.h"
#include "AnimNotify_PlayHowl.h"

void UAnimNotify_PlayHowl::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;


    ABaseCharacter* Char = Cast<ABaseCharacter>(Owner);
    if (Char)
    {

        Char->PlayHowlAtLocation(VolumeMultiplier);
    }
}
