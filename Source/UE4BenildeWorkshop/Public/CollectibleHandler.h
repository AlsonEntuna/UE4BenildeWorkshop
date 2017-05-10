// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CollectibleHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCollectibleHandlerFullEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4BENILDEWORKSHOP_API UCollectibleHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UCollectibleHandler();
	UPROPERTY(EditDefaultsOnly, Category = "-- CollectibleHandler Defaults --")
		int32 collectibleMaxCount;
	UFUNCTION(BlueprintCallable, Category = "-- CollectibleHandler Defaults --")
		int32 getCurCollectibleCount() const { return collectibleCount; }
	void addCollectibleCount() const;
	void deductCollectibleCount() const;

	UPROPERTY(BlueprintAssignable, Category = "-- CollectibleHandler Events --")
		FCollectibleHandlerFullEvent CollectibleHandlerFullEvent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	mutable int32 collectibleCount;
	
};
