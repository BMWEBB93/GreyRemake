// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"


AWeapon::AWeapon()
{
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	HitBox->SetupAttachment(RootComponent);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnHitBoxOverlap);

	bRightHand = true;
}

void AWeapon::UseItem()
{
   
	Attack();
}

void AWeapon::Attack()
{

}

void AWeapon::OnHitBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
