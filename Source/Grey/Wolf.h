// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Wolf.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API AWolf : public ABaseCharacter
{
	GENERATED_BODY()
	

public:

	AWolf();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* TreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APatrolPath* PatrolPath;

};
