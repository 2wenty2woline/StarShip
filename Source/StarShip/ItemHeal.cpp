// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHeal.h"
#include "Components/BoxComponent.h"
#include "StarShipCharacter.h"

// Sets default values
AItemHeal::AItemHeal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* Create comp */
	FirsComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirsComp"));
	FirsComp->SetWorldScale3D(FVector(0.25, 0.25, 1));
	FirsComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SecondComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondComp"));
	SecondComp->SetWorldScale3D(FVector(4, 01, 0.25));
	SecondComp->AttachToComponent(FirsComp, FAttachmentTransformRules::KeepRelativeTransform);

	/* Create box collision */
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	CollisionBox->AttachToComponent(FirsComp, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBox->SetWorldScale3D(FVector(7, 4, 2));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItemHeal::OnOverlapBegin);

	/* Heal power */
	HealPower = 20.f;
}

// Called when the game starts or when spawned
void AItemHeal::BeginPlay()
{
	Super::BeginPlay();
}

void AItemHeal::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStarShipCharacter* Character = Cast<AStarShipCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (Character != nullptr && OtherActor == Character)
	{
		if (Character->Health < Character->MaxHealth)
		{
			Character->Health += HealPower;
			Destroy();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, "MaxHealth");
		}
	}
}
