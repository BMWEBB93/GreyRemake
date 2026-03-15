// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetRandomDecision.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"

UBTTask_SetRandomDecision::UBTTask_SetRandomDecision()
{
	bCreateNodeInstance = true;
	NodeName = "SetRandomDecision";
}


EBTNodeResult::Type UBTTask_SetRandomDecision::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check if AIController or Blackboard exist in the AI Character
	UBlackboardComponent* WolfBlackboard = OwnerComp.GetBlackboardComponent();

	if (!WolfBlackboard)
	{
		return EBTNodeResult::Failed;
	}


	float RandomNumber = FMath::RandRange(0.0f, 1.0f);
	WolfBlackboard->SetValueAsFloat("DecisionWeight", RandomNumber);

	return EBTNodeResult::Succeeded;


}
