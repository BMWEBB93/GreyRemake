// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PlayerItem.h"
#include "BuildableObjects.h"
#include "Lighter.h"
#include "CampFire.h"


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
    CameraBoom->CameraLagSpeed = 50.f;
    CameraBoom->CameraLagMaxDistance = 7.f;
    CameraBoom->bEnableCameraRotationLag = true;
    CameraBoom->CameraRotationLagSpeed = 50.f;



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

    // Set up widget
    if (IsValid(WidgetReference))
    {
        Hud = CreateWidget<UHudWidget>(GetWorld(), WidgetReference);

        if (IsValid(Hud))
        {
            Hud->AddToViewport();
        }
    }
    
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);    

    CheckLookAtItem();
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
        enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
        enhancedInputComponent->BindAction(LeftHandAction, ETriggerEvent::Started, this, &APlayerCharacter::LeftHand);
        enhancedInputComponent->BindAction(RightHandAction, ETriggerEvent::Started, this, &APlayerCharacter::RightHand);

        // Item selection
        enhancedInputComponent->BindAction(Item0Action, ETriggerEvent::Started, this, &APlayerCharacter::Item0);
        enhancedInputComponent->BindAction(Item1Action, ETriggerEvent::Started, this, &APlayerCharacter::Item1);
        enhancedInputComponent->BindAction(Item2Action, ETriggerEvent::Started, this, &APlayerCharacter::Item2);
        enhancedInputComponent->BindAction(Item3Action, ETriggerEvent::Started, this, &APlayerCharacter::Item3);
        enhancedInputComponent->BindAction(Item4Action, ETriggerEvent::Started, this, &APlayerCharacter::Item4);
        enhancedInputComponent->BindAction(Item5Action, ETriggerEvent::Started, this, &APlayerCharacter::Item5);
        enhancedInputComponent->BindAction(Item6Action, ETriggerEvent::Started, this, &APlayerCharacter::Item6);
        enhancedInputComponent->BindAction(Item7Action, ETriggerEvent::Started, this, &APlayerCharacter::Item7);
        enhancedInputComponent->BindAction(Item8Action, ETriggerEvent::Started, this, &APlayerCharacter::Item8);
        enhancedInputComponent->BindAction(Item9Action, ETriggerEvent::Started, this, &APlayerCharacter::Item9);


    }
}

// Input actions
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

        float value = LookAxis.Y;
        lookPitch += value;
    }

    // lock between 60 and -60
    if (lookPitch > 60) lookPitch = 60;
    if (lookPitch < -60) lookPitch = -60;    
}

void APlayerCharacter::StartSprint(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;    
}

void APlayerCharacter::StopSprint(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;   
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
    if (LookedAtItem != NULL && HeldItems.Num() < 11) // if looking at a valid item and have space in the inventory
    {
        LookedAtItem->DisableCollision();
        LookedAtItem->Player = this;

        HeldItems.Add(LookedAtItem);
        LookedAtItem->SetOwner(this);

        if (Hud && LookedAtItem->ItemImage)
        {
            int32 Slot = HeldItems.Num() - 1;
            Hud->SetSlotIcon(Slot, LookedAtItem->ItemImage);
        }

        if (LookedAtItem->bRightHand) // item is a right handed item
        {
            if (RightEquippedItem != NULL)
                RightEquippedItem->Uequip();            

            LookedAtItem->AttachToComponent(
                GetMesh(),
                FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                FName("RightHandSocket"));

             LookedAtItem->Equip();
             RightEquippedItem = LookedAtItem;
        }
        else // item is a left handed item
        {
            if (LeftEquippedItem != NULL)
                LeftEquippedItem->Uequip();           

            LookedAtItem->AttachToComponent(
                GetMesh(),
                FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                FName("LeftHandSocket"));

            LookedAtItem->Equip();
            LeftEquippedItem = LookedAtItem;
        }
    }
    
}

void APlayerCharacter::LeftHand(const FInputActionValue& Value)
{
    if (LeftEquippedItem != NULL)
    {
        LeftEquippedItem->UseItem();
    }
}

void APlayerCharacter::RightHand(const FInputActionValue& Value)
{
    if (RightEquippedItem != NULL)
    {
        RightEquippedItem->UseItem();
    }
}

void APlayerCharacter::Item0(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 0)
    {
        if (HeldItems[0]->bRightHand)
        {
            if(RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[0];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[0];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item1(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 1)
    {
        if (HeldItems[1]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[1];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[1];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item2(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 2)
    {
        if (HeldItems[2]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[2];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[2];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item3(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 3)
    {
        if (HeldItems[3]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[3];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[3];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item4(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 4)
    {
        if (HeldItems[4]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[4];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[4];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item5(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 5)
    {
        if (HeldItems[5]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[5];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[5];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item6(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 6)
    {
        if (HeldItems[6]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[6];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[6];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item7(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 7)
    {
        if (HeldItems[7]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[7];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[7];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item8(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 8)
    {
        if (HeldItems[8]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[8];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[8];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::Item9(const FInputActionValue& Value)
{
    if (HeldItems.Num() > 9)
    {
        if (HeldItems[9]->bRightHand)
        {
            if (RightEquippedItem)
                RightEquippedItem->Uequip();

            RightEquippedItem = HeldItems[9];
            RightEquippedItem->Equip();
        }
        else // is a left handed item
        {
            if (LeftEquippedItem)
                LeftEquippedItem->Uequip();

            LeftEquippedItem = HeldItems[9];
            LeftEquippedItem->Equip();
        }
    }
}

void APlayerCharacter::CheckLookAtItem()
{
    if (!FollowCamera)
    {
        return;
    }

    FVector Start = FollowCamera->GetComponentLocation();
    FVector Forward = FollowCamera->GetForwardVector();
    float Length = 400.f;
    FVector End = Start + (Forward * Length);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this); // ignore the player

    // Line trace towards the camera direction
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        Start,
        End,
        ECC_Visibility,
        Params
    );

    
    bCanLightFire = false;

    if (bHit && Hud) // if ray hit and HUD exists
    {
        

        if (APlayerItem* Item = Cast<APlayerItem>(Hit.GetActor())) // cast to item base class
        {
            LookedAtItem = Item;

            Hud->SetItemPreviewText(LookedAtItem->ItemName);                 
        }
        else if (ABuildableObjects* Object = Cast<ABuildableObjects>(Hit.GetActor())) // Cast to buildable objects
        {
            LookedAtObject = Object;
            LookedAtItem = NULL;

            ALighter* Lighter = Cast<ALighter>(LeftEquippedItem);
            ACampFire* Campfire = Cast<ACampFire>(Object);
            if (Campfire)
            {
                FireToLight = Campfire;
            }
            else
            {
                FireToLight = NULL;
            }

            if (Lighter && Campfire && Lighter->bIsLit)
            {
                Hud->SetItemPreviewText(FText::FromString("Start Fire"));
                bCanLightFire = true;
            }      
            else
            {
                Hud->SetItemPreviewText(FText::GetEmpty());
            }
        }
        else
        {
            Hud->SetItemPreviewText(FText::GetEmpty());

            LookedAtItem = NULL;
            LookedAtObject = NULL;
        }
    }
    else
    {
        if (Hud)
        {
            Hud->SetItemPreviewText(FText::GetEmpty());
        }
        LookedAtItem = NULL;
        LookedAtObject = NULL;

    }
    
}

void APlayerCharacter::UpdateInventory()
{
    if (!Hud) return;

    if (HeldItems.Num() > 0)
    {
        for (int32 i = 0; i < HeldItems.Num(); i++)
        {
            Hud->SetSlotIcon(i, HeldItems[i]->ItemImage);

        }

    }
    for (int32 i = 0; i < 10 - HeldItems.Num(); i++)
    {
        Hud->SetSlotIcon(i + HeldItems.Num(), nullptr);             
    }
}

void APlayerCharacter::RemoveItem(APlayerItem* Item)
{
    Item->Uequip();
    HeldItems.Remove(Item);

    if (RightEquippedItem == Item)
    {
        RightEquippedItem = nullptr;
    }
    if (LeftEquippedItem == Item)
    {
        LeftEquippedItem = nullptr;
    }

    UpdateInventory();
}




