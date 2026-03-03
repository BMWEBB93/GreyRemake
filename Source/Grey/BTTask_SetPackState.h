// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PackState.h"

#include "BTTask_SetPackState.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_SetPackState : public UBTTaskNode
{
	GENERATED_BODY()
	

public:

	UBTTask_SetPackState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	EPackState DesiredPackState;
};
