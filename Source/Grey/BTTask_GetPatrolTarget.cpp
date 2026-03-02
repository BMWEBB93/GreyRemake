// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetPatrolTarget.h"
#include "Wolf.h"
#include "WolfPack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AIController.h"



UBTTask_GetPatrolTarget::UBTTask_GetPatrolTarget()
{
	bCreateNodeInstance = true;
	NodeName = "GetPatrolTarget";
}

EBTNodeResult::Type UBTTask_GetPatrolTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check if AIController or Blackboard exist in the AI Character
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* WolfController = OwnerComp.GetAIOwner();

	if (!WolfController || !MyBlackboard)
	{
		return EBTNodeResult::Failed;
	}

	//check if the pawn of the AIController is an instance of AI character
	AWolf* myWolf = Cast<AWolf>(WolfController->GetPawn());

	if (!myWolf)
	{
		return EBTNodeResult::Failed;
	}

	AWolfPack* WolfPack = myWolf->Pack;
	AWolf* TargetWolf = WolfPack->GetPatrolFollowTarget(myWolf);
	MyBlackboard->SetValueAsObject("TargetActor", TargetWolf);


	return EBTNodeResult::Succeeded;
}
