#include "Player Controller/PC_Game.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void APC_Game::BeginPlay()
{
    Super::BeginPlay();
}

void APC_Game::SetupInputComponent()
{
    Super::SetupInputComponent();

    // get the enhanced input subsystem
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        // add the mapping context so we get controls
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }
}