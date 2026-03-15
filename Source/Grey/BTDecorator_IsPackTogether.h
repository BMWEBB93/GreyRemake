// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsPackTogether.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API UBTDecorator_IsPackTogether : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public: 
	UBTDecorator_IsPackTogether();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


public:
	UPROPERTY(EditAnywhere, Category = "Range")
	float MaxDistance = 1000.f;
};
