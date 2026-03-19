// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetWolfState.h"
#include "WolfAiController.h"

UBTTask_SetWolfState::UBTTask_SetWolfState()
{
	bCreateNodeInstance = true;
	NodeName = "SetWolfState";
}

EBTNodeResult::Type UBTTask_SetWolfState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Get AI Controller
    AAIController* Controller = OwnerComp.GetAIOwner();
    if (!Controller)
    {
        return EBTNodeResult::Failed;
    }

    AWolfAiController* WolfController = Cast<AWolfAiController>(Controller);
    if (!WolfController)
    {
        return EBTNodeResult::Failed;
    }

    WolfController->SetWolfState(DesiredState);

    return EBTNodeResult::Succeeded;

}
