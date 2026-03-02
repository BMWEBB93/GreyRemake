// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetMovementSpeed.h"

#include "AIController.h"
#include "Wolf.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_SetMovementSpeed::UBTTask_SetMovementSpeed()
{
	bCreateNodeInstance = true;
	NodeName = "SetMovementSpeed";
}

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check if AIController or Blackboard exist in the AI Character
	const UBlackboardComponent* WolfBlackboard = OwnerComp.GetBlackboardComponent();
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

	Wolf->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	return EBTNodeResult::Succeeded;

}
