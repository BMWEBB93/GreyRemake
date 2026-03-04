// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetSurroundPoint.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_GetSurroundPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public: 
	UBTTask_GetSurroundPoint();

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
