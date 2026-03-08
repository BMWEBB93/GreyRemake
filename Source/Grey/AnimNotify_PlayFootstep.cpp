// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_PlayFootstep.h"

#include "Wolf.h"
#include "PlayerCharacter.h"

void UAnimNotify_PlayFootstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    
    ABaseCharacter* Char = Cast<ABaseCharacter>(Owner); 
    if (Char)
    {
       
        Char->PlayFootstepAtLocation(VolumeMultiplier);
    }

}
