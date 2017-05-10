// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4BenildeWorkshop.h"
#include "UE4BenildeWorkshopCharacter.h"
#include "CollectibleHandler.h"
#include "Collectible.h"


ACollectible::ACollectible(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	collectibleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collectibleCollider;
	collectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collectibleMesh->SetupAttachment(collectibleCollider);
}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();

	charRef = Cast<AUE4BenildeWorkshopCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(charRef);
	
	if (collectibleCollider)
		collectibleCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::onComponentBeginOverlap);
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectible::onComponentBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor == charRef)
	{
		if (ParticleToPlay)
			UGameplayStatics::SpawnEmitterAtLocation(this, ParticleToPlay, GetActorLocation(), GetActorRotation(), true);
		if (charRef != nullptr)
			if (charRef->CollectibleHandler != nullptr)
				if (CollectibleType == ECollectibleType::CT_GOOD)
					charRef->CollectibleHandler->addCollectibleCount();
				else if (CollectibleType == ECollectibleType::CT_BAD)
					charRef->CollectibleHandler->deductCollectibleCount();
		Destroy();
	}
}

