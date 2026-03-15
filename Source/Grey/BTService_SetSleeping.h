// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetSleeping.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTService_SetSleeping : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	

public:
	UBTService_SetSleeping();

protected:
	virtual void OnBecomeRelevant( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp,	uint8* NodeMemory) override;
};
