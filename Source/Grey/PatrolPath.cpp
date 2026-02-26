// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolPath.h"


#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"


// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
	Billboard->SetupAttachment(GetRootComponent());
	FacingDirection = CreateDefaultSubobject<UArrowComponent>("FacingDirection");
	FacingDirection->SetupAttachment(Billboard);
	Path = CreateDefaultSubobject<USplineComponent>("Path");
	Path->SetupAttachment(RootComponent);
	Path->bDrawDebug = true;
}

// Called when the game starts or when spawned
void APatrolPath::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i <= Path->GetNumberOfSplinePoints(); i++)
		Locations.Add(Path->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));

}



