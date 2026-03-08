// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "Components/BoxComponent.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API AWeapon : public APlayerItem
{
	GENERATED_BODY()


public: 
	AWeapon();

	virtual void UseItem() override;
	virtual void Attack();

	UFUNCTION()
	void OnHitBoxOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


protected:

	UPROPERTY(EditAnywhere)
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadOnly)
	bool bCanHit = false;
};
