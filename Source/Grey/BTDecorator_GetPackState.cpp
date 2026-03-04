// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_GetPackState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Wolf.h"
#include "WolfPack.h"

UBTDecorator_GetPackState::UBTDecorator_GetPackState()
{

	NodeName = "GetPackState";
	bCreateNodeInstance = true;
}

bool UBTDecorator_GetPackState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            1.5f,
            FColor::Green,
            FString::Printf(TEXT("State"))
        );
    }

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
    return Wolf->Pack->CurrentPackState == DesiredPackState;
}
