// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_hasLineOfSight.h"

#include "WolfAIController.h"
#include "Wolf.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"


UBTDecorator_hasLineOfSight::UBTDecorator_hasLineOfSight()
{
	NodeName = "hasLineOfSight";
	bCreateNodeInstance = true;
}


bool UBTDecorator_hasLineOfSight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,	uint8* NodeMemory) const
{
	//check if AIController or Blackboard exist in the AI Character
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (!MyController || !MyBlackboard)
		return false;
	//check if the pawn of the AIController is an instance of AI character
	AWolf* MyWolf = Cast<AWolf>(MyController->GetPawn());
	if (!MyWolf)
		return false;
	//Get main character detected, push forward for the Engage sequence
	if (MyBlackboard->GetValueAsBool("HasLineOfSight"))
		return true;
	return false;
}
