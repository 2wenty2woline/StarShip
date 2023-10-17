// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarShipGameMode.h"
#include "StarShipCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStarShipGameMode::AStarShipGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
