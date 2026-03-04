// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	speed = GetVelocity().Size2D();
	bIsInAir = GetCharacterMovement()->IsFalling();

	// get movement direction for animation
	FVector Velocity = GetVelocity();
	FVector Forward = GetActorForwardVector();

	float ForwardDot = FVector::DotProduct(Forward, Velocity);
	float RightDot = FVector::DotProduct(GetActorRightVector(), Velocity);

	movementDirection = FMath::Atan2(RightDot, ForwardDot) * (180.f / PI);
}

void ABaseCharacter::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0) CurrentHealth = 0; bIsDead = true;
}

void ABaseCharacter::Heal(float HealAmount)
{
	CurrentHealth += HealAmount;
	if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
}




void ABaseCharacter::PlayFootstepAtLocation(float Volume)
{
	if (FootstepSounds.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, FootstepSounds.Num() - 1);
		USoundBase* RandFootstepSound = FootstepSounds[Index];

		float Pitch = FMath::RandRange(0.9f, 1.1f);
		UGameplayStatics::PlaySoundAtLocation(this, RandFootstepSound, GetActorLocation(), Volume, Pitch, 0.f, FootstepAttenuation);
	}	
}


void ABaseCharacter::PlayHowlAtLocation(float Volume)
{
	if (HowlSounds.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, HowlSounds.Num() - 1);
		USoundBase* RandHowlSound = HowlSounds[Index];

		float Pitch = FMath::RandRange(0.9f, 1.1f);
		UGameplayStatics::PlaySoundAtLocation(this, RandHowlSound, GetActorLocation(), Volume, Pitch, 0.f, HowlAttenuation);
	}
}


void ABaseCharacter::PlayGrowlAtLocation(float Volume)
{
	if (GrowlSounds.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, GrowlSounds.Num() - 1);
		USoundBase* RandGrowlSound = GrowlSounds[Index];

		float Pitch = FMath::RandRange(0.9f, 1.1f);
		UGameplayStatics::PlaySoundAtLocation(this, RandGrowlSound, GetActorLocation(), Volume, Pitch, 0.f, GrowlAttenuation);
	}
}

