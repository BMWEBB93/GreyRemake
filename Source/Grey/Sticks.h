// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "BuildableObjects.h"
#include "CampFire.h"

#include "Sticks.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API ASticks : public APlayerItem
{
	GENERATED_BODY()
	

public:

	ASticks();

	UFUNCTION(BlueprintCallable)
	virtual void UseItem() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Equip();
	virtual void Uequip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACampFire> CampFire;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ACampFire* CampFirePreview;
};
