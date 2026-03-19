// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_GetPackAttackState.h"

#include "PackAttack.h"
#include "Wolf.h"
#include "WolfAiController.h"

UBTDecorator_GetPackAttackState::UBTDecorator_GetPackAttackState()
{
	NodeName = "GetPackAttackState";
	bCreateNodeInstance = true;
}

bool UBTDecorator_GetPackAttackState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{


    // Get AI Controller
    AAIController* WolfController = OwnerComp.GetAIOwner();
    if (!WolfController)
    {
        return false;
    }

    // Get controlled Wolf
    AWolf* Wolf = Cast<AWolf>(WolfController->GetPawn());
    if (!Wolf || !Wolf->Pack)
    {
        return false;
    }





    // Compare with the actual pack state
    return Wolf->Pack->CurrentPackAttack == DesiredState;
}
