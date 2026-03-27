// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"

#include "CampFire.h"

#include "PlayerItem.h"
#include "Lighter.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API ALighter : public APlayerItem
{
	GENERATED_BODY()

public:

	ALighter();


	virtual void UseItem() override;
	virtual void Equip();
	virtual void Uequip();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LighterCap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* Flame;

	UPROPERTY()
	UNiagaraComponent* FlameComponent;

	bool bIsLit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPointLightComponent* Light;

	float LightMaxIntensity = 500.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* LightFireMontage;

	
};
