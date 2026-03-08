// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerItem.h"

// Sets default values
APlayerItem::APlayerItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = ItemMesh;

}

// Called when the game starts or when spawned
void APlayerItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerItem::UseItem()
{
}

void APlayerItem::DisableCollision()
{
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Turn off collision
	ItemMesh->SetSimulatePhysics(false);    // Turn off physics
	ItemMesh->SetEnableGravity(false);      // Turn off gravity
}

void APlayerItem::EnableCollision()
{
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Turn on collision
	ItemMesh->SetSimulatePhysics(true);    // Turn on physics
	ItemMesh->SetEnableGravity(true);      // Turn on gravity

}

void APlayerItem::Uequip()
{
	ItemMesh->SetVisibility(false);           // Hide mesh
	bIsEquipped = false;
}

void APlayerItem::Equip()
{
	ItemMesh->SetVisibility(true);   
	bIsEquipped = true;
}

