// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPackAttackState.h"
#include "Wolf.h"
#include "WolfPack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AIController.h"
#include "PackAttack.h"

UBTTask_SetPackAttackState::UBTTask_SetPackAttackState()
{
	bCreateNodeInstance = true;
	NodeName = "SetPackState";
}

EBTNodeResult::Type UBTTask_SetPackAttackState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (!myWolf || !myWolf->Pack)
	{
		return EBTNodeResult::Failed;
	}

	AWolfPack* WolfPack = myWolf->Pack;
	WolfPack->SetPackAttackState(DesiredPackAttackState);
	return EBTNodeResult::Succeeded;
}
