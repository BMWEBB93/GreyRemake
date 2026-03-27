// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableObjects.h"

// Sets default values
ABuildableObjects::ABuildableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = ItemMesh;

	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Turn off collision
	ItemMesh->SetSimulatePhysics(false);    // Turn on physics
	ItemMesh->SetEnableGravity(false);      // Turn on gravity
}

// Called when the game starts or when spawned
void ABuildableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildableObjects::BuildObject()
{
	if (ItemMesh && BuiltMaterial)
	{
		ItemMesh->SetMaterial(0, BuiltMaterial); 
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Turn on collision
		bIsBuilt = true;
	}
}

