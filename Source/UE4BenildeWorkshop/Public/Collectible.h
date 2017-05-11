// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

class AUE4BenildeWorkshopCharacter;
class ACollectibleBank;

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
	/*Enum for the type of collectible*/
	UPROPERTY(EditDefaultsOnly, Category = "-- Collectible Defaults --")
		ECollectibleType CollectibleType;
	/*Particle System of the Collectible to be played when the character hits it*/
	UPROPERTY(EditDefaultsOnly, Category = "-- Collectible Defaults --")
		UParticleSystem* ParticleToPlay;
	/*Sound Cue to be played*/
	UPROPERTY(EditDefaultsOnly, Category = "-- Collectible Defaults --")
		USoundCue* CollectSFX;
	/*Delegate function to be assigned to the overlap event*/
	UFUNCTION(BlueprintCallable, Category  = "-- Collectible Functions --")
		virtual void onComponentBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	/*CollectibleBank Reference*/
	UPROPERTY(VisibleAnywhere, Category = "-- Public Attributes --")
		ACollectibleBank* CollectibleBankRef;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* collectibleMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* collectibleCollider;
	
	AUE4BenildeWorkshopCharacter* charRef;
	
};
