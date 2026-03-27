// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerItem.h"
#include "Radio.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API ARadio : public APlayerItem
{
	GENERATED_BODY()
	

public:
	ARadio();

	virtual void UseItem() override;
	virtual void Equip();
};
