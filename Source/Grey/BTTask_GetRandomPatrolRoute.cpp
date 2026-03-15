// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomPatrolRoute.h"

#include "WolfPack.h"
#include "AIController.h"
#include "Wolf.h"
#include "PatrolPath.h"


UBTTask_GetRandomPatrolRoute::UBTTask_GetRandomPatrolRoute()
{
	bCreateNodeInstance = true;
	NodeName = "GetRandomPatrolRoute";
}

EBTNodeResult::Type UBTTask_GetRandomPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check if AIController or Blackboard exist in the AI Character
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
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

	//Check if PatrolPath reference is valid and locations are populated
	AWolfPack* WolfPack = Cast<AWolfPack>(myWolf->Pack);
	WolfPack->SetRandPatrolPath();

	return EBTNodeResult::Succeeded;

}
