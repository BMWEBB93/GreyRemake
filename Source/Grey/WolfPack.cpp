// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfPack.h"
#include "Wolf.h"
#include "Kismet/GameplayStatics.h"
#include "Algo/Sort.h"


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
	
	// sort wolves by size
	PackMembers.Sort([](const AWolf& A, const AWolf& B)
	{
			return A.GetActorScale3D().X > B.GetActorScale3D().X;
	});

	AlphaWolf = PackMembers[0];
	PackMembers[0]->bIsAlpha = true;
	for (int32 i = 0; i < PackMembers.Num(); i++) 
	{
		PackMembers[i]->HierarchyRank = i;
	}

}

// Called every frame
void AWolfPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

