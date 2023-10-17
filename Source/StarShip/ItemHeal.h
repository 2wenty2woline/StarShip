// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemHeal.generated.h"

class UBoxComponent;

UCLASS()
class STARSHIP_API AItemHeal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemHeal();

	/** Heal comp **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FirsComp")
	UStaticMeshComponent* FirsComp;

	/**  Heal comp **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SecondComp")
	UStaticMeshComponent* SecondComp;

	/** Collision Box **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CollisionBox")
	UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Overlap Healing */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Heal power **/
	float HealPower;
};
