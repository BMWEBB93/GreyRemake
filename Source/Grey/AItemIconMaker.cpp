// Fill out your copyright notice in the Description page of Project Settings.


#include "AItemIconMaker.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
AAItemIconMaker::AAItemIconMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>("PreviewMesh");
    RootComponent = PreviewMesh;

    CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("CaptureComponent");
    CaptureComponent->SetupAttachment(RootComponent);

    RenderTarget = NewObject<UTextureRenderTarget2D>();
    RenderTarget->InitAutoFormat(128, 128); // low resolution icon

    CaptureComponent->TextureTarget = RenderTarget;
}

UTextureRenderTarget2D* AAItemIconMaker::CaptureMesh(UStaticMesh* Mesh)
{
    if (!Mesh) return nullptr;

    PreviewMesh->SetStaticMesh(Mesh);

    CaptureComponent->CaptureScene();

    return RenderTarget;
}



