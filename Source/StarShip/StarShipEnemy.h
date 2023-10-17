// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "StarShipEnemy.generated.h"

UCLASS()
class STARSHIP_API AStarShipEnemy : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AStarShipEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Static mesh character **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMeshComponent")
	UStaticMeshComponent* StaticMeshComponent;

	/** Sphere Collision **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackingCollusion")
	USphereComponent* SphereCollision;

	/** Health **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	/** Health **/
	float Health;

	/** Is Dead **/
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const;

	/** Take Damage **/
	void TakeDamage(int32& Damage);
};
