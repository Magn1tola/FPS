// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "CharacterModificationSystem/ModInstallerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractionSystem/InteractorComponent.h"
#include "InventorySystem/ActorsMagnetComponent.h"
#include "InventorySystem/DroppedItem.h"
#include "InventorySystem/InventoryComponent.h"
#include "Player/FPSPlayerState.h"
#include "WeaponSystem/WeaponInventoryComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APlayerCharacter

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f),
	                                                           FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	ModInstallerComponent = CreateDefaultSubobject<UModInstallerComponent>(TEXT("ModInstaller"));
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	MagnetComponent = CreateDefaultSubobject<UActorsMagnetComponent>(TEXT("Dropped Items Magnet"));
	MagnetComponent->AttractingClass = ADroppedItem::StaticClass();
	
	WeaponInventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>(TEXT("Weapon Inventory"));

	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor"));

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	ThirdPersonWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Third Person Weapon SKM"));
	ThirdPersonWeaponMesh->SetupAttachment(GetMesh(), FName("HandGrip_R"));
	ThirdPersonWeaponMesh->SetOwnerNoSee(true);
	ThirdPersonWeaponMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacter::LookInput);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void APlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	if (GetController())
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	}
}

void APlayerCharacter::LookInput(const FInputActionValue& Value)
{
	if (GetController())
	{
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::InitAbilitySystemComponent()
{
	AFPSPlayerState* FPSPlayerState = GetPlayerState<AFPSPlayerState>();
	check(FPSPlayerState);
	
	AbilitySystemComponent = CastChecked<UFPSAbilitySystemComponent>(FPSPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(FPSPlayerState, this);
	
	HealthAttributes = FPSPlayerState->GetPlayerAttributes();
	WeaponAttributes = FPSPlayerState->GetWeaponAttributes();
	BodyEnergyAttributes = FPSPlayerState->GetBodyEnergyAttributes();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	InitDefaultAttributes();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
	InitDefaultAttributes();
}
