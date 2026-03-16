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
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


AWolfAiController::AWolfAiController() 
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BBC = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");	

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	SetPerceptionComponent(*PerceptionComponent);

	// Sight config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	SightConfig->SightRadius = AiSightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;



	// Hearing config
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->HearingRange = HearingRange;
	HearingConfig->SetMaxAge(AiHearingAge);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;


	PerceptionComponent->ConfigureSense(*HearingConfig);
	PerceptionComponent->ConfigureSense(*SightConfig);

	PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AWolfAiController::OnPawnDetected);


}


void AWolfAiController::BeginPlay()
{
	Super::BeginPlay();
}


void AWolfAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	
	
}


void AWolfAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AWolf* MyWolf = Cast<AWolf>(InPawn);
	if (MyWolf && MyWolf->TreeAsset)
	{
		BBC->InitializeBlackboard(*MyWolf->TreeAsset->BlackboardAsset);
		BTC->StartTree(*MyWolf->TreeAsset);

		EnemyKeyID = BBC->GetKeyID("Enemy");
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

	



	bool bPlayerSeen = false;
	bool bHeardSomething = false;

	for (AActor* Detected : DetectedPawns)
	{
		FActorPerceptionBlueprintInfo Info;
		PerceptionComponent->GetActorsPerception(Detected, Info);

		


		for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
		{
			

			// Sight
			if (Stimulus.Type == UAISense_Sight::StaticClass()->GetDefaultObject<UAISense>()->GetSenseID())
			{
				

				if (Detected == UGameplayStatics::GetPlayerPawn(this, 0))
				{			
					bPlayerSeen = true;
					DistanceToPlayer = GetPawn()->GetDistanceTo(Detected);
					BBC->SetValue<UBlackboardKeyType_Bool>("bHasLineOfSight", true);
					BBC->SetValue<UBlackboardKeyType_Object>("Enemy", Detected);
					BBC->SetValueAsVector("LastEnemyLocation", Detected->GetActorLocation());
				}
			}

			// Hearing
			if (Stimulus.Type == UAISense_Hearing::StaticClass()->GetDefaultObject<UAISense>()->GetSenseID())
			{			
				if (Stimulus.WasSuccessfullySensed())
				{					
					bHeardSomething = true;
					BBC->SetValue<UBlackboardKeyType_Bool>("bHeardNoise", true);
					BBC->SetValue<UBlackboardKeyType_Object>("HeardActor", Detected);
				}
			}
		}		
	}	

	if (!bPlayerSeen || DistanceToPlayer > AiSightRadius)
	{
		BBC->SetValue<UBlackboardKeyType_Bool>("bHasLineOfSight", false);
		BBC->ClearValue("Enemy");
	}

	if (!bHeardSomething)
	{
		BBC->SetValue<UBlackboardKeyType_Bool>("bHeardNoise", false);
		BBC->ClearValue("HeardActor");
	}
}


AActor* AWolfAiController::GetSeeingPawn()
{
	UObject* object = BBC->GetValueAsObject(BlackboardEnemyKey);
	return object ? Cast<AActor>(object) : nullptr;
}

void AWolfAiController::SetupPackData()
{

	AWolf* MyWolf = Cast<AWolf>(GetPawn());
	if (!MyWolf) return;	

	if (BBC)
	{
		BBC->SetValueAsObject("AlphaWolf", MyWolf->AlphaWolf);
		BBC->SetValueAsBool("bIsAlpha", MyWolf->bIsAlpha);
		BBC->SetValueAsInt("HierarchyRank", MyWolf->HierarchyRank);
	}
}