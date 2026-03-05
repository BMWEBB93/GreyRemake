// Fill out your copyright notice in the Description page of Project Settings.


#include "EQC_FindHidingSpot.h"
#include "WolfAiController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UFindEnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	AWolfAiController* WolfContoller = Cast<AWolfAiController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (WolfContoller && WolfContoller->GetSeeingPawn())
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, WolfContoller->GetSeeingPawn());
}
