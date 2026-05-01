// Fill out your copyright notice in the Description page of Project Settings.


#include "CampFire.h"

#include "Kismet/GameplayStatics.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ACampFire::ACampFire()
{
	FireLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FireLight"));
	FireLight->SetupAttachment(RootComponent);

	FireLight->Intensity = 0.f;
	FireLight->AttenuationRadius = 2000.f;
	FireLight->SourceRadius = 15.f;
	FireLight->SoftSourceRadius = 8.f;

	FireLight->SetRelativeLocation(FVector(0, 0, 20.f));
}


void ACampFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	HandlePlayerPlacement();

	if (FireLight && bIsLit)
	{
		float Time = GetWorld()->GetTimeSeconds();

		float Flicker = FMath::Sin(Time * 5.f) * 800.f;
		Flicker += FMath::PerlinNoise1D(Time * 2.f) * 600.f;

		FireLight->SetIntensity(5000.f + Flicker);
	}
}

void ACampFire::BeginPlay()
{
	if (bShouldStartLit)
	{
		StartFire();
	}
}


void ACampFire::HandlePlayerPlacement()
{
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
		float SphereRadius = 50.f;
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

void ACampFire::StartFire()
{
	if (!FireComponent)
	{
		FireComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			Fire,
			ItemMesh,
			FName("FlameSocket"),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			false);

		bIsLit = true;

		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation(), Volume, Pitch, 0.f, FireAttenuation);
		FireLight->SetIntensity(FireLightMaxIntensity);
	}
}
