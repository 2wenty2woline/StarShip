// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarShipCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AStarShipCharacter

AStarShipCharacter::AStarShipCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	/* Set size for collision capsule */
	GetCapsuleComponent()->InitCapsuleSize(40.f, 40.0f);
	GetArrowComponent();

	/* Create static mesh */
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetSimulatePhysics(true);

	/* Create a CameraComponent */
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-20.f, 0.f, 20.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	/* Create a Weapon */
	Weapon = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("Weapon"));

	/* Health */
	MaxHealth = 100.f;
	Health = MaxHealth;
}

void AStarShipCharacter::OnAnyDamageRecieved(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || Health <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	/* If health 0.0f kill character */
	if (Health <= 0.0f)
	{
		Destroy();
	}
}

void AStarShipCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	/* Add AnyDamage */
	this->OnTakeAnyDamage.AddDynamic(this, &AStarShipCharacter::OnAnyDamageRecieved);

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AStarShipCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStarShipCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStarShipCharacter::Look);

		/* Going UP */
		EnhancedInputComponent->BindAction(UpAction, ETriggerEvent::Triggered, this, &AStarShipCharacter::GoingUp);

		/* Fire */
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AStarShipCharacter::Fire);
	}
}


void AStarShipCharacter::Move(const FInputActionValue& Value)
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

void AStarShipCharacter::GoingUp(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorUpVector(), MovementVector.Z);
	}
}

float AStarShipCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AStarShipCharacter::Look(const FInputActionValue& Value)
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

void AStarShipCharacter::Fire()
{
	Weapon->Fire(this);
}
