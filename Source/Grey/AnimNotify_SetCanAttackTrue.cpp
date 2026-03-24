// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_SetCanAttackTrue.h"

#include "BaseCharacter.h"


void UAnimNotify_SetCanAttackTrue::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;


}
