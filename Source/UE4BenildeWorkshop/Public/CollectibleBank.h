// Copyright UE4 Benilde Workshop 2017

#pragma once

#include "GameFramework/Actor.h"
#include "CollectibleBank.generated.h"

class ACollectible;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCollectibleCollectedEvent, ACollectible*, collectedCollectible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCollectibleBankEmptyEvent);

UCLASS()
class UE4BENILDEWORKSHOP_API ACollectibleBank : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectibleBank();
	UPROPERTY(VisibleAnywhere, Category = "-- Public Attributes --")
		TArray<ACollectible*> Collectibles;
	UPROPERTY(BlueprintAssignable, Category = "-- CollectibleBank Events --")
		FCollectibleBankEmptyEvent CollectibleBankEmptyEvent;

	FCollectibleCollectedEvent CollectibleCollectedEvent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void onCollectibleCollectedEvent(ACollectible* p_collectible);

	
	
};
