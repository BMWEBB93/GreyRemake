// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetIsAttacking.h"

#include "BaseCharacter.h"

void UAnimNotify_SetIsAttacking::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;


    ABaseCharacter* Char = Cast<ABaseCharacter>(Owner);
    if (Char)
    {
        Char->SetIsAttacking(state);
    }

}
