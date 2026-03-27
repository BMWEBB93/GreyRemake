// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "BuildableObjects.h"
#include "TentBuilt.h"

#include "Tent.generated.h"



/**
 * 
 */
UCLASS()
class GREY_API ATent : public APlayerItem
{
	GENERATED_BODY()
	


public:

	ATent();

	UFUNCTION(BlueprintCallable)
	virtual void UseItem() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Equip();
	virtual void Uequip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATentBuilt> PlaceableTent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATentBuilt* TentPreview;
};
