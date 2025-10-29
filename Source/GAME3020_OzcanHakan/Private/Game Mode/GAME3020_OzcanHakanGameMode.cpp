// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game Mode/GAME3020_OzcanHakanGameMode.h"
#include "Character/GAME3020_OzcanHakanCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAME3020_OzcanHakanGameMode::AGAME3020_OzcanHakanGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
