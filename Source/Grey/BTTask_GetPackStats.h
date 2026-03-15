// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPackStats.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_GetPackStats : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	
public:
	UBTTask_GetPackStats();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
