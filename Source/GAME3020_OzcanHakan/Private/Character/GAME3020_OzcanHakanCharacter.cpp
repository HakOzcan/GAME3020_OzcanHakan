// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/GAME3020_OzcanHakanCharacter.h"
#include "GAME3020_OzcanHakanProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "HUD/HUD_Game.h"
#include "Components/Grabber.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGAME3020_OzcanHakanCharacter

AGAME3020_OzcanHakanCharacter::AGAME3020_OzcanHakanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AGAME3020_OzcanHakanCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AGAME3020_OzcanHakanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////// Input

void AGAME3020_OzcanHakanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGAME3020_OzcanHakanCharacter::Move);

		// Looking
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGAME3020_OzcanHakanCharacter::Look);

		// Pausing
		EnhancedInput->BindAction(PauseAction, ETriggerEvent::Completed, this, &AGAME3020_OzcanHakanCharacter::Pause);

		// Grabbing
		EnhancedInput->BindAction(GrabAction, ETriggerEvent::Started, this, &AGAME3020_OzcanHakanCharacter::Grab);

		// Releasing
		EnhancedInput->BindAction(GrabAction, ETriggerEvent::Completed, this, &AGAME3020_OzcanHakanCharacter::Release);

#if PLATFORM_SWITCH
		EnhancedInput->BindAction(BackActionBottom, ETriggerEvent::Completed, this, &AGAME3020_OzcanHakanCharacter::Back);
#else
		EnhancedInput->BindAction(BackActionRight, ETriggerEvent::Completed, this, &AGAME3020_OzcanHakanCharacter::Back);
#endif
	}

	// If using legacy input, some custom logic might be needed instead
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AGAME3020_OzcanHakanCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGAME3020_OzcanHakanCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGAME3020_OzcanHakanCharacter::Pause()
{
	if (!UGameplayStatics::IsGamePaused(GetWorld())) // NOT PAUSED
	{
		if (PauseMenuWidgetClass)
		{
			PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);

			if (PauseMenuWidget)
			{
				UGameplayStatics::SetGamePaused(GetWorld(), true);
				PauseMenuWidget->AddToViewport();

				FInputModeGameAndUI InputMode;
				APlayerController* PC = Cast<APlayerController>(GetController());
				if (PC)
				{
					PC->SetInputMode(InputMode);
				}

				if (PC)
				{
					AHUD_Game* HUD = PC->GetHUD<AHUD_Game>();
					if (HUD)
					{
						HUD->HideGameHUD();
					}
				}
			}
		}
	}
	else // PAUSED
	{
		Back();
	}
}


void AGAME3020_OzcanHakanCharacter::Grab()
{
	if (UGrabber* Grabber = FindComponentByClass<UGrabber>())
	{
		Grabber->Grab();
	}
}

void AGAME3020_OzcanHakanCharacter::Release()
{
	if (UGrabber* Grabber = FindComponentByClass<UGrabber>())
	{
		Grabber->Release();
	}
}

void AGAME3020_OzcanHakanCharacter::Back()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		if (PauseMenuWidget)
		{
			PauseMenuWidget->RemoveFromParent();
		}

		FInputModeGameOnly InputMode;
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->SetInputMode(InputMode);
			AHUD_Game* HUD = PC->GetHUD<AHUD_Game>();
			if (HUD)
			{
				HUD->DisplayGameHUD();
			}
		}
	}
}