// Fill out your copyright notice in the Description page of Project Settings.


#include "StarShipEnemy.h"

// Sets default values
AStarShipEnemy::AStarShipEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* Create static mesh */
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	/* Create sphere collision */
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollusion"));
	SphereCollision->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SphereCollision->InitSphereRadius(600.f);

	/* Health */
	MaxHealth = 100.f;
	Health = MaxHealth;

}

// Called when the game starts or when spawned
void AStarShipEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AStarShipEnemy::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}

void AStarShipEnemy::TakeDamage(int32& Damage)
{
	Health -= Damage;

	if (IsDead())
	{
		Destroy();
	}
}
