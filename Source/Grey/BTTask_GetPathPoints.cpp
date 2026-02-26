// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetPathPoints.h"

#include "AIController.h"
#include "Components/SplineComponent.h"
#include "Wolf.h"
#include "PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_GetPathPoints::UBTTask_GetPathPoints()
{
	bCreateNodeInstance = true;
	NodeName = "GetPathPoints";
}

EBTNodeResult::Type UBTTask_GetPathPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check if AIController or Blackboard exist in the AI Character
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* WolfController = OwnerComp.GetAIOwner();

	if (!WolfController || !MyBlackboard)
		return EBTNodeResult::Failed;

	//check if the pawn of the AIController is an instance of AI character
	AWolf* myWolf = Cast<AWolf>(WolfController->GetPawn());

	if (!myWolf)
		return EBTNodeResult::Failed;

	//Check if PatrolPath reference is valid and locations are populated
	APatrolPath* PathRef = Cast<APatrolPath>(myWolf->PatrolPath);

	if (!PathRef || PathRef->Locations.Num() < 1)
		return EBTNodeResult::Succeeded;
	

	//Set the MoveToLocation Blackboard key to be the spline point
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>("MoveToLocation",
		PathRef->Locations[Index]);
	if (Index < PathRef->Locations.Num() - 1) {
		Index++;
		return EBTNodeResult::Succeeded;
	}
	Index = 1;
	return EBTNodeResult::Succeeded;
}



