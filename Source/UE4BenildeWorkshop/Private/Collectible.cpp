// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4BenildeWorkshop.h"
#include "UE4BenildeWorkshopCharacter.h"
#include "CollectibleHandler.h"
#include "CollectibleBank.h"
#include "Collectible.h"


ACollectible::ACollectible(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) // Initialization Lists
{
	PrimaryActorTick.bCanEverTick = false;// We don't want to use tick so we should turn it false to save memory

	// Create collectible components using CreateDefaultSubobject<T>
	collectibleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collectibleCollider; // Assign the rootcomponent of this actor to the collider
	collectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collectibleMesh->SetupAttachment(collectibleCollider); // Make the other remaining components attach to the root component to avoid transformation matrix errors and parenting
}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the character/player in the game using GamePlayStatics class and cast it to our own class
	charRef = Cast<AUE4BenildeWorkshopCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(charRef);
	
	// Initialize the delegate for the collision dection of the collider
	if (collectibleCollider)
		collectibleCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::onComponentBeginOverlap);
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectible::onComponentBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Check if the detected actor is the character
	if (OtherActor == charRef)
	{
		// Raise the event to the CollectibleBank Reference
		if (CollectibleBankRef != nullptr)
			CollectibleBankRef->CollectibleCollectedEvent.Broadcast(this);

		// Spawn Particles
		if (ParticleToPlay)
			UGameplayStatics::SpawnEmitterAtLocation(this, ParticleToPlay, GetActorLocation(), GetActorRotation(), true);

		// Play the sound at the location of this object/actor
		if (CollectSFX)
			UGameplayStatics::PlaySoundAtLocation(this, CollectSFX, GetActorLocation());

		// Know whether the type is GOOD or BAD then do the logic to add or deduct the count of the collectible
		if (charRef != nullptr)
			if (charRef->CollectibleHandler != nullptr)
				if (CollectibleType == ECollectibleType::CT_GOOD)
					charRef->CollectibleHandler->addCollectibleCount();
				else if (CollectibleType == ECollectibleType::CT_BAD)
					charRef->CollectibleHandler->deductCollectibleCount();
		Destroy();
	}
}

