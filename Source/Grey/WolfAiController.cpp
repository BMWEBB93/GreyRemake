// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfAiController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Waypoint.h"
#include "Wolf.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


AWolfAiController::AWolfAiController() 
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BBC = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");	

	PrimaryActorTick.bCanEverTick = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception"));
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AWolfAiController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}


void AWolfAiController::BeginPlay()
{
	Super::BeginPlay();
}


void AWolfAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DistanceToPlayer > AISightRadius)
	{
		BBC->SetValue<UBlackboardKeyType_Bool>("HasLineOfSight", false);
		BBC->ClearValue("TargetActor");		
	}
}


void AWolfAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AWolf* MyWolf = Cast<AWolf>(InPawn);
	if (MyWolf && MyWolf->TreeAsset)
	{
		BBC->InitializeBlackboard(*MyWolf->TreeAsset->BlackboardAsset);
		EnemyKeyID = BBC->GetKeyID("TargetActor");
		BTC->StartTree(*MyWolf->TreeAsset);
	}
}


FRotator AWolfAiController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
		return FRotator(.0f, 0.f, 0.f);
	else
		return FRotator(.0f, GetPawn()->GetActorRotation().Yaw, .0f);
}


void AWolfAiController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for (size_t i = 0; i < DetectedPawns.Num(); i++) 
	{
		if (DetectedPawns[i] == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
			BBC->SetValue<UBlackboardKeyType_Bool>("HasLineOfSight", true);
			BBC->SetValue<UBlackboardKeyType_Object>("TargetActor", DetectedPawns[i]);
		}
	}	
}