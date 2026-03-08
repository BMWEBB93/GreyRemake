// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

#include "PlayerItem.h"

#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GREY_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Mapping context
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    class UInputMappingContext* DefaultMappingContext;


    // Input actions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* SprintAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* InteractAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* LeftHandAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* RightHandAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item0Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item1Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item2Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item3Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item4Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item5Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item6Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item7Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item8Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* Item9Action;




    // Animation variables
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float lookPitch;

    

    // Movement variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 300.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed = 800.f;


    // Inventory
    UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<APlayerItem*> HeldItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    APlayerItem* LeftEquippedItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    APlayerItem* RightEquippedItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    APlayerItem* LookedAtItem;



    // Camera boom (spring arm)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* CameraBoom;

    // Follow camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;
        
    // Widget
    UPROPERTY (EditDefaultsOnly, Category = "UI")
    TSubclassOf <class UUserWidget> WidgetReference;

    UPROPERTY()
    UUserWidget* CreatedWidget;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Input Actions
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartSprint(const FInputActionValue& Value);
    void StopSprint(const FInputActionValue& Value);
    void Interact(const FInputActionValue& Value);
    void LeftHand(const FInputActionValue& Value);
    void RightHand(const FInputActionValue& Value);

    void Item0(const FInputActionValue& Value);
    void Item1(const FInputActionValue& Value);
    void Item2(const FInputActionValue& Value);
    void Item3(const FInputActionValue& Value);
    void Item4(const FInputActionValue& Value);
    void Item5(const FInputActionValue& Value);
    void Item6(const FInputActionValue& Value);
    void Item7(const FInputActionValue& Value);
    void Item8(const FInputActionValue& Value);
    void Item9(const FInputActionValue& Value);

    void CheckLookAtItem();
    




};
