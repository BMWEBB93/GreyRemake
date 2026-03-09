// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AItemIconMaker.generated.h"


class USceneCaptureComponent2D;
class UStaticMeshComponent;
class UTextureRenderTarget2D;

UCLASS()
class GREY_API AAItemIconMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAItemIconMaker();


	UTextureRenderTarget2D* CaptureMesh(UStaticMesh* Mesh);

protected:
	UPROPERTY()
	USceneCaptureComponent2D* CaptureComponent;

	UPROPERTY()
	UStaticMeshComponent* PreviewMesh;

	UPROPERTY()
	UTextureRenderTarget2D* RenderTarget;

public:	
	// Called every frame

};
