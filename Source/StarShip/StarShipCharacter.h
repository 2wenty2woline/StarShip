// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "StarShipProjectile.h"
#include "TP_WeaponComponent.h"
#include "StarShipCharacter.generated.h"

class UInputComponent;
class USceneComponent;
class UCameraComponent;

UCLASS(config=Game)
class AStarShipCharacter : public ACharacter
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Going Up Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* UpAction;

	/* Take damage */
	UFUNCTION()
	void OnAnyDamageRecieved(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:
	virtual void BeginPlay();

public:

	AStarShipCharacter();
	
	/** Static mesh character **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMeshComponent")
	UStaticMeshComponent* StaticMeshComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Weapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTP_WeaponComponent* Weapon;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AStarShipProjectile> ProjectileClass;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Health **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	/* Health */
	float Health;

	/** Get Health **/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Going UP **/
	void GoingUp(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Fire */
	void Fire();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
};

