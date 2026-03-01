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

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* TreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWaypoint* NextWayPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HierarchyRank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAlpha = false;

	// Movement variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 900.f;

};
