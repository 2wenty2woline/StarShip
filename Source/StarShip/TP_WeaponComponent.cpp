// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "StarShipCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(50.0f, 0.0f, 0.0f);
	MaxAmmo = 10;
	Ammo = MaxAmmo;
}

void UTP_WeaponComponent::Fire(AStarShipCharacter* TargetCharacter)
{
	if (TargetCharacter == nullptr || TargetCharacter->GetController() == nullptr)
	{
		return;
	}

	if (Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, "None Ammo");
		return;
	}

	// Try and fire a projectile
	if (TargetCharacter->ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(TargetCharacter->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = TargetCharacter->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			World->SpawnActor<AStarShipProjectile>(TargetCharacter->ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			/* shoot 1 ammo */
			Ammo -= 1;
		}
	}
}