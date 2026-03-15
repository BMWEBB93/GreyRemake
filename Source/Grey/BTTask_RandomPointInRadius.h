// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomPointInRadius.generated.h"



/**
 * 
 */
UCLASS()
class GREY_API UBTTask_RandomPointInRadius : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	UBTTask_RandomPointInRadius();

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector OriginActorKey;	

	UPROPERTY(EditAnywhere, Category = "AI")
	float Radius = 800.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
