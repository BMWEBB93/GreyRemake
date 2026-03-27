// Fill out your copyright notice in the Description page of Project Settings.


#include "Radio.h"

ARadio::ARadio()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemName = FText::FromString("Radio");
	AnimationType = EAnimationType::Radio;


}

void ARadio::UseItem()
{

}


void ARadio::Equip()
{
	Super::Equip();

	// Correct the rotation/position to fit in  the hand
	SetActorRelativeRotation(FRotator(270.f, 0.f, 0.f));
	SetActorRelativeLocation(FVector(-15.f, -.5f, -1.5f));
}
