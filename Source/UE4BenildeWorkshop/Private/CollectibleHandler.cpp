// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4BenildeWorkshop.h"
#include "CollectibleHandler.h"


UCollectibleHandler::UCollectibleHandler() : collectibleCount(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCollectibleHandler::BeginPlay()
{
	Super::BeginPlay();	
}

void UCollectibleHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollectibleHandler::addCollectibleCount() const
{
	if (collectibleCount > collectibleMaxCount) return;
	++collectibleCount;
	if (collectibleCount >= collectibleMaxCount)
		CollectibleHandlerFullEvent.Broadcast();
}

void UCollectibleHandler::deductCollectibleCount() const
{
	if (collectibleCount <= 0) return;
	--collectibleCount;
}

