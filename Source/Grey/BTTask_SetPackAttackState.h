// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PackAttack.h"
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetPackAttackState.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTTask_SetPackAttackState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTTask_SetPackAttackState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	EPackAttack DesiredPackAttackState;
};
