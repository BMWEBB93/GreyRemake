// Fill out your copyright notice in the Description page of Project Settings.


#include "Hatchet.h"
#include "BaseCharacter.h"

AHatchet::AHatchet()
{
	ItemName = FText::FromString("Hatchet");
	AnimationType = EAnimationType::Axe;
}

void AHatchet::Attack()
{

    

    // Get the owner of the weapon (the character holding it)
    ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // Get the AnimInstance
    UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
    if (!AnimInstance) return;


    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,                        // Key: -1 = always add new message
            5.f,                       // Time to display in seconds
            FColor::Red,               // Color of the text
            TEXT("Hatchet swing!")      // Message
        );
    }


    if (AttackMontage)
    {
        AnimInstance->Montage_Play(AttackMontage, 1.0f);
    }
}
