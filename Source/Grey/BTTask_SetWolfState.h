// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackState.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetWolfState.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_SetWolfState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	


public:

	UBTTask_SetWolfState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackState")
	EPackState DesiredState;

};
