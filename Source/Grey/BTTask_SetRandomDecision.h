// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetRandomDecision.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_SetRandomDecision : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_SetRandomDecision();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
