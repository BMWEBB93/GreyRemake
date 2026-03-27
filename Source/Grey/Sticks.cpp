// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Sticks.h"
#include "Camera/CameraComponent.h"

ASticks::ASticks()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASticks::UseItem()
{
	if (CampFirePreview->bIsValidLocation)
	{
		CampFirePreview->BuildObject();
		Player->RemoveItem(this);
		Destroy();

	}
}

void ASticks::BeginPlay()
{
}

void ASticks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASticks::Equip()
{
	Super::Equip();

	UCameraComponent* Camera;

	// Get the player camera
	if (Player)
	{
		Camera = Player->FollowCamera;


		if (CampFire)
		{

			FVector SpawnLocation;

			FVector Start = Camera->GetComponentLocation();
			FVector Forward = Camera->GetForwardVector();
			float Length = 800.f;
			FVector End = Start + (Forward * Length);

			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(Player); // ignore the player

			// Line trace towards the camera direction
			bool bHit = GetWorld()->LineTraceSingleByChannel(
				Hit,
				Start,
				End,
				ECC_Visibility,
				Params
			);

			if (bHit) // if ray hit
			{
				SpawnLocation = Hit.Location;
			}
			else
			{
				SpawnLocation = End;
			}

			CampFirePreview = GetWorld()->SpawnActor<ACampFire>(CampFire, SpawnLocation, Player->GetActorRotation());

			CampFirePreview->ItemMesh->SetMaterial(0, CampFirePreview->PreviewMaterial);
			CampFirePreview->ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Turn off collision
			CampFirePreview->Camera = Camera;
		}
	}
}


void ASticks::Uequip()
{


	if (IsValid(CampFirePreview))
	{
		if (!CampFirePreview->bIsBuilt)
		{
			CampFirePreview->Destroy();
		}
	}

	Super::Uequip();

}
