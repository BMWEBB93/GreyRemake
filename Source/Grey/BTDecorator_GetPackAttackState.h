// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackAttack.h"

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_GetPackAttackState.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTDecorator_GetPackAttackState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTDecorator_GetPackAttackState();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	EPackAttack DesiredState;

};
