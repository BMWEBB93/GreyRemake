// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PackState.h"
#include "PackAttack.h"
#include "WolfPack.generated.h"




class AWolf;
UCLASS()
class GREY_API AWolfPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWolfPack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TArray<AWolf*> PackMembers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	AWolf* AlphaWolf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	AWolf* FollowTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	EPackState CurrentPackState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	EPackAttack CurrentPackAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APatrolPath* CurrentPatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<APatrolPath*> AvailablePatrolPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PackMorale = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PackStamina = 100.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateHierarchy();
	virtual void SetPackState(EPackState NewState);
	void SetPackAttackState(EPackAttack NewState);


	AWolf* GetPatrolFollowTarget(AWolf* SelfWolf);

	FVector GetSurroundTargetPosition(AWolf* Wolf, AActor* TargetActor, float Radius = 600.f);

	void SetRandPatrolPath();
};
