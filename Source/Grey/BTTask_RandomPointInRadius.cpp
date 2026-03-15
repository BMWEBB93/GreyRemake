// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomPointInRadius.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Wolf.h"
#include "WolfAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


UBTTask_RandomPointInRadius::UBTTask_RandomPointInRadius()
{
	bCreateNodeInstance = true;
	NodeName = "SetRandomPointInRadius";
}

EBTNodeResult::Type UBTTask_RandomPointInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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


	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys)
	{

		return EBTNodeResult::Failed;
	}

	FNavLocation Result;

	AActor* OriginActor = Cast<AActor>(WolfBlackboard->GetValueAsObject(OriginActorKey.SelectedKeyName));

	if (!OriginActor)
	{
		return EBTNodeResult::Failed;
	}

	if (NavSys && NavSys->GetRandomReachablePointInRadius(OriginActor->GetActorLocation(),Radius,Result))
	{
		WolfBlackboard->SetValueAsVector("MoveToLocation", Result.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
