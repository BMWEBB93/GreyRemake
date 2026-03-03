// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_TargetMovesAway.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Wolf.h"
#include "WolfPack.h"

UBTDecorator_TargetMovesAway::UBTDecorator_TargetMovesAway()
{
	NodeName = "TargetLeavesRange";
	bCreateNodeInstance = true;
}

bool UBTDecorator_TargetMovesAway::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return false;

    AActor* Target = Cast<AActor>(BB->GetValueAsObject("TargetActor"));
    if (!IsValid(Target)) return false;

    float Distance = FVector::Dist(Wolf->GetActorLocation(), Target->GetActorLocation());

    return Distance > MaxDistance;

}
