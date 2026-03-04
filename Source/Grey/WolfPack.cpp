// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfPack.h"
#include "Wolf.h"
#include "WolfAiController.h"
#include "Kismet/GameplayStatics.h"
#include "Algo/Sort.h"

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
	TArray <AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolf::StaticClass(), FoundActors);

	PackMembers.Empty();
	for (AActor* Actor : FoundActors)
	{
		if (AWolf* Wolf = Cast<AWolf>(Actor))
		{
			PackMembers.Add(Wolf);
			Wolf->Pack = this;
		}
	}

	// Randomize sizes first
	for (AWolf* Wolf : PackMembers)
	{
		if (Wolf)
		{
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

		AWolfAiController* AI = Cast<AWolfAiController>(PackMembers[i]->GetController());
		AI->SetupPackData();
	}

	FollowTarget = AlphaWolf;
}

AWolf* AWolfPack::GetPatrolFollowTarget(AWolf* SelfWolf)
{
	AWolf* Target = FollowTarget;

	FollowTarget = SelfWolf;

	return PackMembers[0];
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

