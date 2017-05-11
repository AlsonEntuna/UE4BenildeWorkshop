// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

class AUE4BenildeWorkshopCharacter;

UENUM(BlueprintType)
enum class ECollectibleType : uint8
{
	CT_GOOD UMETA(DisplayName = "GOOD"),
	CT_BAD UMETA(DisplayName = "BAD"),
	CT_COUNT UMETA(DisplayName = "COUNT")
};

UCLASS()
class UE4BENILDEWORKSHOP_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectible(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly, Category = "-- Collectible Defaults --")
		ECollectibleType CollectibleType;
	UPROPERTY(EditDefaultsOnly, Category = "-- Collectible Defaults --")
		UParticleSystem* ParticleToPlay;
	UPROPERTY(EditDefaultsOnly, Category = "-- Collectible Defaults --")
		USoundCue* CollectSFX;
	UFUNCTION(BlueprintCallable, Category  = "-- Collectible Functions --")
		virtual void onComponentBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* collectibleMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* collectibleCollider;
	
	AUE4BenildeWorkshopCharacter* charRef;
	
};
