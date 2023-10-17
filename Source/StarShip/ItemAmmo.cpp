// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAmmo.h"
#include "Components/BoxComponent.h"
#include "StarShipCharacter.h"

// Sets default values
AItemAmmo::AItemAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* Create comp */
	AmmoStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirsComp"));
	AmmoStaticMesh->SetWorldScale3D(FVector(0.25, 0.25, 0.25));
	AmmoStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	/* Sphere collision */
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetWorldScale3D(FVector(2, 2, 2));
	CollisionBox->BodyInstance.SetCollisionProfileName("CollisionBox");
	CollisionBox->AttachToComponent(AmmoStaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItemAmmo::OnOverlapBegin);

	/* Ammo Count */
	AmmoCount = 1;
}

// Called when the game starts or when spawned
void AItemAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemAmmo::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStarShipCharacter* Character = Cast<AStarShipCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (Character != nullptr && OtherActor == Character)
	{
		if (Character->Weapon->Ammo < Character->Weapon->MaxAmmo)
		{
			Character->Weapon->Ammo += AmmoCount;
			Destroy();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, "MaxAmmo");
		}
	}
}
