// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AWolf::AWolf() 
{
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.f);

	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(.0f, 600.f, .0f);

}