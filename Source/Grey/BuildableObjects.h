// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"

#include "BuildableObjects.generated.h"

UCLASS()
class GREY_API ABuildableObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildableObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BuildObject();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* PreviewMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* BuiltMaterial;

	UPROPERTY(EditAnywhere)
	UMaterial* InvalidMaterial;

	UCameraComponent* Camera;


	bool bIsValidLocation = false;

	bool bIsBuilt = false;
};
