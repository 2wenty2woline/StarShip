// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AStarShipCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHIP_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire(AStarShipCharacter* TargetCharacter);

	/* Ammo */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Ammo;

	/* Ammo */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxAmmo;
};
