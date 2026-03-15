// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfPack.h"
#include "Wolf.h"
#include "WolfAiController.h"
#include "Kismet/GameplayStatics.h"
#include "Algo/Sort.h"
#include "PackState.h"


#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AWolfPack::AWolfPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWolfPack::BeginPlay()
{
	Super::BeginPlay();


	// get all wolves in level and add to pack 
	/*TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolf::StaticClass(), FoundActors);

	PackMembers.Empty();
	for (AActor* Actor : FoundActors)
	{
		if (AWolf* Wolf = Cast<AWolf>(Actor))
		{
			if (Wolf->Pack == NULL)
			{
				PackMembers.Add(Wolf);
			}
			
		}
	}*/

	// Randomize sizes first
	for (AWolf* Wolf : PackMembers)
	{
		if (Wolf)
		{
			Wolf->Pack = this;

			float RandomScale = FMath::FRandRange(0.9f, 1.2f);
			Wolf->SetActorScale3D(FVector(RandomScale));
		}
	}
	
	GetWorldTimerManager().SetTimerForNextTick(this, &AWolfPack::UpdateHierarchy);

}

// Called every frame
void AWolfPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (AWolf* Wolf : PackMembers)
	{
		if (!Wolf) continue;

		AAIController* Controller = Cast<AAIController>(Wolf->GetController());
		if (!Controller) continue;

		UBlackboardComponent* BB = Controller->GetBlackboardComponent();
		if (!BB) continue;

		BB->SetValueAsFloat("PackMorale", PackMorale);
		BB->SetValueAsFloat("PackStamina", PackStamina);
	}
	
	switch (CurrentPackState)
	{
	case EPackState::Idle:

		if (PackStamina < 100.f)
			PackStamina += 0.01f;

		break;

	case EPackState::Patrolling:

		if (PackStamina > 0.f)
			PackStamina -= 0.001f;

		break;

	case EPackState::Hunting:

		if(PackMorale < 100.f)
			PackMorale += .001f;
	
		if (PackStamina > 0.f)
			PackStamina -= 0.002f;

		break;

	case EPackState::Attacking:
		if(PackMorale < 100.f)
			PackMorale += .01f;

		if (PackStamina > 0.f)
			PackStamina -= 0.01f;

		break;

	default:
		break;
	}




	

}

void AWolfPack::UpdateHierarchy()
{
	// sort wolves by size
	PackMembers.Sort([](const AWolf& A, const AWolf& B)
	{
		return A.GetActorScale3D().X > B.GetActorScale3D().X;
	});

	AlphaWolf = PackMembers[0];
	PackMembers[0]->bIsAlpha = true;
	for (int32 i = 0; i < PackMembers.Num(); i++)
	{
		PackMembers[i]->AlphaWolf = PackMembers[0];
		PackMembers[i]->HierarchyRank = i;

		PackMembers[i]->GetCharacterMovement()->AvoidanceWeight = i;

		AWolfAiController* AI = Cast<AWolfAiController>(PackMembers[i]->GetController());
		AI->SetupPackData();
	}

	FollowTarget = AlphaWolf;
}

AWolf* AWolfPack::GetPatrolFollowTarget(AWolf* SelfWolf)
{
	if (!SelfWolf)
		return nullptr;

	int32 Rank = SelfWolf->HierarchyRank;

	// Alpha leads
	if (Rank == 0)
		return nullptr;

	// Follow the wolf above in hierarchy
	return PackMembers[Rank - 1];
}

FVector AWolfPack::GetSurroundTargetPosition(AWolf* Wolf, AActor* TargetActor, float Radius)
{
	if (!Wolf || !TargetActor || PackMembers.Num() == 0)
		return FVector::ZeroVector;

	// Find the wolfs index in array
	int32 Index = PackMembers.IndexOfByKey(Wolf);
	if (Index == INDEX_NONE)
		return FVector::ZeroVector;

	FVector Centre = TargetActor->GetActorLocation();
	float AngleDifference = 360.f / PackMembers.Num();
	float AngleDeg = AngleDifference * Index;

	float AngleRad = FMath::DegreesToRadians(AngleDeg);

	// Offset vector from the target
	FVector Offset;
	Offset.X = FMath::Cos(AngleRad) * Radius;
	Offset.Y = FMath::Sin(AngleRad) * Radius;
	Offset.Z = 0.f;


	return Centre + Offset;
}

void AWolfPack::SetRandPatrolPath()
{
	int32 RandomIndex = FMath::RandRange(0, AvailablePatrolPaths.Num() - 1);

	CurrentPatrolPath = AvailablePatrolPaths[RandomIndex];
}

void AWolfPack::SetPackState(EPackState NewState)
{
	CurrentPackState = NewState;

	for (AWolf* Wolf : PackMembers)
	{
		if (!Wolf) continue;

		AAIController* Controller = Cast<AAIController>(Wolf->GetController());
		if (!Controller) continue;

		UBlackboardComponent* BB = Controller->GetBlackboardComponent();
		if (!BB) continue;

		BB->SetValueAsEnum("PackState", (uint8)NewState);
		
	}
}

