// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetPackStats.h"

#include "AIController.h"
#include "Wolf.h"
#include "WolfPack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"

UBTTask_GetPackStats::UBTTask_GetPackStats()
{
	bCreateNodeInstance = true;
	NodeName = "GetPackStats";
}

EBTNodeResult::Type UBTTask_GetPackStats::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	// check if AIController or Blackboard exist in the AI Character
	UBlackboardComponent* WolfBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* WolfController = OwnerComp.GetAIOwner();

	if (!WolfController || !WolfBlackboard)
	{
		return EBTNodeResult::Failed;
	}

	//check if the pawn of the AIController is an instance of AI character
	AWolf* Wolf = Cast<AWolf>(WolfController->GetPawn());

	if (!Wolf)
	{
		return EBTNodeResult::Failed;
	}

	AWolfPack* Pack = Wolf->Pack;

	if (!Pack)
	{
		return EBTNodeResult::Failed;
	}

	WolfBlackboard->SetValueAsFloat("PackMorale", Pack->PackMorale);
	WolfBlackboard->SetValueAsFloat("PackStamina", Pack->PackStamina);


	return EBTNodeResult::Succeeded;
}
