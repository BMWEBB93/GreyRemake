// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetSleeping.h"
#include "Wolf.h"
#include "AIController.h"

UBTService_SetSleeping::UBTService_SetSleeping()
{
	NodeName = "SetSleeping";

}

void UBTService_SetSleeping::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Wolf Sleeping"));

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	AWolf* Wolf = Cast<AWolf>(Controller->GetPawn());
	if (!Wolf) return;

	Wolf->bIsSleeping = true;

	
}

void UBTService_SetSleeping::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	AWolf* Wolf = Cast<AWolf>(Controller->GetPawn());
	if (!Wolf) return;

	Wolf->bIsSleeping = false;
}
