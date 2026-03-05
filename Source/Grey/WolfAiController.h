// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "WolfAiController.generated.h"

/**
 * 
 */

class AWolf;
UCLASS()
class GREY_API AWolfAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	AWolfAiController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* MyPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;
	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	AActor* GetSeeingPawn();
	const FName BlackboardEnemyKey = FName("Enemy");

	void SetupPackData();


	// AI perception variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float AISightRadius = 1500.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float AISightAge = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float AILoseSightRadius = AISightRadius + 50.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float AIFieldOfView = 140.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DistanceToPlayer = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsPlayerDetected = false;

	

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BTC;
	UPROPERTY(transient)
	class UBlackboardComponent* BBC;
	uint16 EnemyKeyID; //This variable is not used today, but a usual practice

protected:

};
