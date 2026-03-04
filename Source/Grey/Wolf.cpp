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
	GetCharacterMovement()->RotationRate = FRotator(.0f, 300.f, .0f);
	GetCharacterMovement()->MaxAcceleration = 1000.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;


	

}

void AWolf::BeginPlay()
{
	Super::BeginPlay();

	
}



