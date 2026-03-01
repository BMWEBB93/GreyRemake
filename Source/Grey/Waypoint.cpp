// Fill out your copyright notice in the Description page of Project Settings.
#include "Waypoint.h"

#include "Wolf.h"

// Sets default values
AWaypoint::AWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject <USceneComponent>("Root");
	SetRootComponent(Root);
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(GetRootComponent());
	Box->OnComponentBeginOverlap.AddDynamic(this, &AWaypoint::OnPlayerEnter);
}

void AWaypoint::OnPlayerEnter(UPrimitiveComponent* OverlapComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{
	AWolf* Character = nullptr;
	if (OtherActor != nullptr)
	{
		Character = Cast<AWolf>(OtherActor);
		if (Character != nullptr)
			Character->NextWayPoint = NextWayPoint;
	}
}

