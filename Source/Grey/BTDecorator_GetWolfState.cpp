// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_GetWolfState.h"

#include "WolfAiController.h"

UBTDecorator_GetWolfState::UBTDecorator_GetWolfState()
{
	NodeName = "GetWolfState";
	bCreateNodeInstance = true;
}

bool UBTDecorator_GetWolfState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    // Get AI Controller
    AAIController* Controller = OwnerComp.GetAIOwner();
    if (!Controller)
    {
        return false;
    }

    // Get the current state of wolf and compare with thedesired state
    AWolfAiController* WolfController = Cast<AWolfAiController>(Controller);
    return WolfController->WolfState == DesiredPackState;
}
