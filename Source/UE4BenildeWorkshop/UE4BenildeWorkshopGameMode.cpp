// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UE4BenildeWorkshop.h"
#include "UE4BenildeWorkshopGameMode.h"
#include "UE4BenildeWorkshopCharacter.h"

AUE4BenildeWorkshopGameMode::AUE4BenildeWorkshopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MC_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
