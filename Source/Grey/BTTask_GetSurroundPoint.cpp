// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetSurroundPoint.h"
#include "WolfPack.h"
#include "AIController.h"
#include "Wolf.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"



UBTTask_GetSurroundPoint::UBTTask_GetSurroundPoint()
{
	bCreateNodeInstance = true;
	NodeName = "GetSurroundPoint";
}

EBTNodeResult::Type UBTTask_GetSurroundPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	//Get Wolf pack
	AWolfPack* WolfPack = Cast<AWolfPack>(myWolf->Pack);

	AActor* TargetActor = Cast<AActor>(MyBlackboard->GetValueAsObject(TargetActorKey.SelectedKeyName));

	MyBlackboard->SetValue<UBlackboardKeyType_Vector>("MoveToLocation", WolfPack->GetSurroundTargetPosition(myWolf, TargetActor, 800.f));
	return EBTNodeResult::Succeeded;
}
