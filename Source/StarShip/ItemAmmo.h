// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemAmmo.generated.h"

class UBoxComponent;

UCLASS()
class STARSHIP_API AItemAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemAmmo();

	/** Ammo static mesh **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AmmoStaticMesh")
	UStaticMeshComponent* AmmoStaticMesh;

	/** Collision Box **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CollisionBox")
	UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Overlap Healing **/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Ammo Count **/
	int32 AmmoCount;
};
