// GM_Game.cpp
// Implementation of the gameplay game mode.

#include "Game Mode/GM_Game.h"
#include "Player Controller/PC_Game.h"                  // Custom gameplay player controller
#include "HUD/HUD_Game.h"                               // Custom gameplay HUD class
#include "Character/GAME3020_OzcanHakanCharacter.h"     // Gameplay character (pawn) class
#include "GI_Template.h"                                // Custom Game Instance class
#include "Kismet/GameplayStatics.h"                     // Utility for gameplay functions

/**
 * Constructor: Sets up the gameplay-specific classes.
 */
AGM_Game::AGM_Game()
{
    // Set the custom gameplay player controller.
    PlayerControllerClass = APC_Game::StaticClass();

    // Set the custom gameplay HUD.
    HUDClass = AHUD_Game::StaticClass();

    // Set the default pawn (character) class to our gameplay character.
    DefaultPawnClass = AGAME3020_OzcanHakanCharacter::StaticClass();
}

/**
 * StartPlay: Called when the game mode begins play.
 *
 * This function performs the following:
 *  - Retrieves our custom game instance.
 *  - Creates a player controller if a valid controller ID is available.
 *  - Sets the input mode to Game Only.
 *  - Plays the gameplay music.
 *  - Triggers the Blueprint event to initiate gameplay logic.
 */
void AGM_Game::StartPlay()
{
    Super::StartPlay();

    // Retrieve the game instance and cast it to our custom type.
    UGI_Template* GameInstanceRef = Cast<UGI_Template>(UGameplayStatics::GetGameInstance(this));
    if (GameInstanceRef)
    {
        // Check if a valid controller ID exists.
        if (GameInstanceRef->GetActiveControllerID() > -1)
        {
            // Create the player controller for the given controller ID.
            APlayerController* PC = UGameplayStatics::CreatePlayer(this, GameInstanceRef->GetActiveControllerID());

            // Set the input mode to Game Only to ignore UI input.
            FInputModeGameOnly InputMode;
            PC->SetInputMode(InputMode);
        }

        // Play the gameplay music using the game instance.
        GameInstanceRef->PlayGameplayMusic();
    }

    // Call the BlueprintNativeEvent to begin gameplay logic.
    BeginGameplayLogic();
}

/**
 * Default implementation for BeginGameplayLogic.
 * Designers can override this function in Blueprint to implement:
 *  - Timer countdown logic.
 *  - Collectible object management.
 *  - Level success/failure conditions.
 *
 * The default C++ implementation does nothing.
 */
void AGM_Game::BeginGameplayLogic_Implementation()
{
    // Default: No gameplay logic is executed here.
    // Blueprint designers should override this event in BP_GM_Game.
}