// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_DoStatesMatch.h"

#include "WolfAiController.h"
#include "Wolf.h"
#include "WolfPack.h"
#include "PackState.h"

UBTDecorator_DoStatesMatch::UBTDecorator_DoStatesMatch()
{
	NodeName = "WolfStateMatchesPackState";
	bCreateNodeInstance = true;
}

bool UBTDecorator_DoStatesMatch::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	// check if AIController or Blackboard exist in the AI Character
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* Controller = OwnerComp.GetAIOwner();
	AWolfAiController* WolfController = Cast<AWolfAiController>(Controller);

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
	if (!WolfPack)
	{
		return EBTNodeResult::Failed;
	}

	if (WolfController->WolfState == WolfPack->CurrentPackState)
	{
		return true;
	}
	else
	{
		return false;
	}

}
