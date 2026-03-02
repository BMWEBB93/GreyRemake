// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPatrolTarget.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_GetPatrolTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_GetPatrolTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
