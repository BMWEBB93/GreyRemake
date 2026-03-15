// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetResting.h"
#include "Wolf.h"
#include "AIController.h"

UBTService_SetResting::UBTService_SetResting()
{
	NodeName = "SetResting";

}

void UBTService_SetResting::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Wolf Resting Relevant"));

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	AWolf* Wolf = Cast<AWolf>(Controller->GetPawn());
	if (!Wolf) return;

	Wolf->bIsResting = true;

	
}

void UBTService_SetResting::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	AWolf* Wolf = Cast<AWolf>(Controller->GetPawn());
	if (!Wolf) return;

	Wolf->bIsResting = false;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Wolf Resting End"));
}

void UBTService_SetResting::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
}
