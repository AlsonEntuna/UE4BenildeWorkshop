// Copyright UE4 Benilde Workshop 2017

#include "UE4BenildeWorkshop.h"
#include "Collectible.h"
#include "CollectibleBank.h"

ACollectibleBank::ACollectibleBank()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACollectibleBank::BeginPlay()
{
	Super::BeginPlay();

	// Initialize an array of actors for you to use as a storage
	TArray<AActor*> temp;
	// Use to get all actors of type ACollectible in the game world/level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectible::StaticClass(), temp);

	// Double check if the array is not empty before iterating through the collection
	if (temp.Num() != 0)
	{
		// Iterate through the temp list of actors
		for (const auto& mem : temp)
		{
			// Check if casting fails or not and if it doesn't fail then add the casted object to the actual collectible list since AActor != ACollectible and we should cast it before we add it to the list
			ACollectible* col = Cast<ACollectible>(mem);
			if (col)
			{
				Collectibles.Add(col);
				// Assign the reference of the collectibleBankRef
				col->CollectibleBankRef = this;
			}
		}
	}

	// Initialize the delegate for the event
	CollectibleCollectedEvent.AddDynamic(this, &ACollectibleBank::onCollectibleCollectedEvent);
}

void ACollectibleBank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectibleBank::onCollectibleCollectedEvent(ACollectible* p_collectible)
{
	// Don't forget to check if the array is empty or not because in C++ when you try to remove an elem in an empty array it will cause your program to crash
	if (Collectibles.Num() != 0)
	{
		// Check if the parameter is already contained in the list and if it contained then removed it
		if (Collectibles.Contains(p_collectible))
			Collectibles.Remove(p_collectible);
	}
	
	// Check if the bank is already empty or not then if it is empty then raise the last event to end the game which will be read by the level blueprint
	if (Collectibles.Num() <= 0)
		CollectibleBankEmptyEvent.Broadcast();
}
