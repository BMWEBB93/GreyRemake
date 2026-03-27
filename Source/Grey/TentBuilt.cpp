// Fill out your copyright notice in the Description page of Project Settings.


#include "TentBuilt.h"


ATentBuilt::ATentBuilt()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}


void ATentBuilt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// Move the tent preview to the camera look direction
	if (Camera && !bIsBuilt)
	{
		bIsValidLocation = true;

		FVector PreviewLocation;

		FVector Start = Camera->GetComponentLocation();
		FVector Forward = Camera->GetForwardVector();
		float Length = 800.f;
		FVector End = Start + (Forward * Length);

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

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
			PreviewLocation = Hit.Location;
		}
		else
		{
			PreviewLocation = End;
			bIsValidLocation = false;
		}

		SetActorLocation(PreviewLocation);

		// Check the location to see if theres space to place it there
		FHitResult SphereHit;
		float SphereRadius = 100.f;
		FVector SphereLocation = PreviewLocation + FVector(0, 0, SphereRadius + 20.f);
		FCollisionQueryParams SpereParams;
		SpereParams.AddIgnoredActor(this);

		bool bIsBlocked = GetWorld()->SweepSingleByChannel(
			SphereHit,
			SphereLocation,
			SphereLocation, 
			FQuat::Identity,
			ECC_WorldStatic,
			FCollisionShape::MakeSphere(SphereRadius),
			SpereParams
		);
		if (bIsBlocked)
		{
			bIsValidLocation = false;
		}

		// Set the material based on valid placement location
		if (bIsValidLocation)
		{
			ItemMesh->SetMaterial(0, PreviewMaterial);
		}
		else
		{
			ItemMesh->SetMaterial(0, InvalidMaterial);
		}
	}
}

