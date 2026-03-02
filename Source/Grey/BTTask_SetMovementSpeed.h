// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMovementSpeed.generated.h"

/**
 *
 */
UCLASS()
class GREY_API UBTTask_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetMovementSpeed();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float NewSpeed = 300.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
