// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "PackState.h"

#include "BTDecorator_GetWolfState.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTDecorator_GetWolfState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	

public:
	UBTDecorator_GetWolfState();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	EPackState DesiredPackState;

};
