// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

#include "AnimNotify_SetCanAttackTrue.h"

void UAnimNotify_SetCanAttackTrue::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;


}
