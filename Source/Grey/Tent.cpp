// Fill out your copyright notice in the Description page of Project Settings.


#include "Tent.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"


ATent::ATent()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


}

void ATent::UseItem()
{
	if (TentPreview->bIsValidLocation)
	{
		TentPreview->BuildObject();
		Player->RemoveItem(this);
		Destroy();

	}

}

void ATent::BeginPlay()
{
	
}

void ATent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ATent::Equip()
{
	Super::Equip();

	UCameraComponent* Camera;

	// Get the player camera
	if (Player)
	{
		Camera = Player->FollowCamera;		


		if (PlaceableTent)
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

			TentPreview = GetWorld()->SpawnActor<ATentBuilt>(PlaceableTent, SpawnLocation, Player->GetActorRotation());

			TentPreview->ItemMesh->SetMaterial(0, TentPreview->PreviewMaterial);
			TentPreview->ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Turn off collision
			TentPreview->Camera = Camera;
		}
	}
	
	
	

	
}

void ATent::Uequip()
{
	

	if (IsValid(TentPreview))
	{
		if (!TentPreview->bIsBuilt)
		{
			TentPreview->Destroy();
		}
	}

	Super::Uequip();
	
}
