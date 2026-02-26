// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetMesh(), TEXT("HeadSocket"));
    CameraBoom->TargetArmLength = 10.f;
    CameraBoom->bUsePawnControlRotation = false;
    CameraBoom->SetRelativeLocation(FVector::ZeroVector);
    CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 90.f));
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 40.f;
    CameraBoom->CameraLagMaxDistance = 7.f;
    CameraBoom->bEnableCameraRotationLag = true;
    CameraBoom->CameraRotationLagSpeed = 40.f;



    // Camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;
    FollowCamera->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));


    // Movement
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->MaxAcceleration = 1000.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

    

}



// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    // setup input mapping context
    if (APlayerController* playerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
        {
            subsystem->AddMappingContext(DefaultMappingContext, 0);
        }

        if (playerController->PlayerCameraManager)
        {
            playerController->PlayerCameraManager->ViewPitchMin = -60.f;
            playerController->PlayerCameraManager->ViewPitchMax = 60.f;
        }
    }   

    
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // get movement direction for animation
    FVector Velocity = GetVelocity();
    FVector Forward = GetActorForwardVector();

    float ForwardDot = FVector::DotProduct(Forward, Velocity);
    float RightDot = FVector::DotProduct(GetActorRightVector(), Velocity);

    movementDirection = FMath::Atan2(RightDot, ForwardDot) * (180.f / PI);
}





// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
    if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
        enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
        enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::StartSprint);
        enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);

    }
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MoveAxis = Value.Get<FVector2D>();


    const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);

    AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::X), MoveAxis.Y);
    AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y), MoveAxis.X);

}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxis = Value.Get<FVector2D>();


    bool bIsLooking = LookAxis.SizeSquared() > 0.1f;
    if (bIsLooking) 
    {
        AddControllerYawInput(LookAxis.X);
        //AddControllerPitchInput(LookAxis.Y);

        float value = LookAxis.Y;
        lookPitch += value;
    }

    // lock between 60 and -60
    if (lookPitch > 60) lookPitch = 60;
    if (lookPitch < -60) lookPitch = -60;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            1,                  // Key (replaces previous message)
            0.f,                // Display for 1 frame
            FColor::Yellow,     // Text color
            FString::Printf(TEXT("LookAxis X: %.3f Y: %.3f | Pitch: %.3f"),
                LookAxis.X, LookAxis.Y, lookPitch)
        );
    }
}

void APlayerCharacter::StartSprint(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(

            2,                  // Message key (replaces previous with same key)
            5.f,                // Display time, 0 = single frame
            FColor::Yellow,     // Text color
            FString::Printf(TEXT("SprintStart"))
        );
    }
}

void APlayerCharacter::StopSprint(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(

            3,                  // Message key (replaces previous with same key)
            5.f,                // Display time, 0 = single frame
            FColor::Yellow,     // Text color
            FString::Printf(TEXT("SprintStop"))
        );
    }
}
