// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsPackTogether.h"

#include "Wolf.h"
#include "WolfPack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsPackTogether::UBTDecorator_IsPackTogether()
{
	NodeName = "IsPackTogether";
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsPackTogether::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

    // Get Wolf Pack
    AWolfPack* WolfPack = Wolf->Pack;
    if (!WolfPack)
    {
        return false;
    }

    AWolf* Alpha = WolfPack->AlphaWolf;
    TArray<AWolf*> Pack = WolfPack->PackMembers;

    // Loop through wolfs to check distance
    bool isTogether = true;
    for (AWolf* CheckedWolf : Pack)
    {
        if (CheckedWolf == Alpha) continue;

        float Distance = FVector::Dist(CheckedWolf->GetActorLocation(), Alpha->GetActorLocation());

        if (Distance > MaxDistance) isTogether = false;
    }

    return isTogether;
}
