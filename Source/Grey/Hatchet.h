// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Hatchet.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API AHatchet : public AWeapon
{
	GENERATED_BODY()
	
public:
	AHatchet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackMontage;
protected:
	virtual void Attack() override;
};
