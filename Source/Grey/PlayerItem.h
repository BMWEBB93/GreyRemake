// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemType.h"
#include "AnimationType.h"
#include "PlayerItem.generated.h"

class APlayerCharacter;
UCLASS()
class GREY_API APlayerItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAnimationType AnimationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;

	UPROPERTY(BlueprintReadWrite)
	bool bRightHand = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEquipped = false;

	
	APlayerCharacter* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseItem();
	virtual void DisableCollision();
	virtual void EnableCollision();
	virtual void Uequip();
	virtual void Equip();
	
};
