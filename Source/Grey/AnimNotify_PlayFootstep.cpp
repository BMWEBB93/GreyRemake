// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PlayFootstep.h"

void UAnimNotify_PlayFootstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    // Example: Call function on wolf
    /*AWolf* Wolf = Cast<AWolf>(Owner);
    if (Wolf)
    {
        Wolf->PlayFootstep(bIsLeftFoot, VolumeMultiplier);
    }*/
}
