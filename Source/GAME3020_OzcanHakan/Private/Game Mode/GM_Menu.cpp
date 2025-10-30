// GM_Menu.cpp
// Implementation of the menu game mode.

#include "Game Mode/GM_Menu.h"
#include "Player Controller/PC_Menu.h"     // Custom menu player controller
#include "HUD/HUD_Menu.h"                  // Custom menu HUD class
#include "GI_Template.h"                   // Custom Game Instance class

/**
 * Constructor: Sets up the menu-specific classes.
 */
AGM_Menu::AGM_Menu()
{
    // Set the custom menu player controller.
    PlayerControllerClass = APC_Menu::StaticClass();

    // Set the custom menu HUD.
    HUDClass = AHUD_Menu::StaticClass();
}

/**
 * StartPlay: Called when the menu mode begins play.
 *
 * This function retrieves the game instance and calls the BlueprintNativeEvent to handle the menu music.
 */
void AGM_Menu::StartPlay()
{
    Super::StartPlay();

    // Trigger the Blueprint event to play menu music.
    PlayMenuMusic();
}

/**
 * Default implementation for PlayMenuMusic.
 * This implementation retrieves the custom game instance and calls its PlayMenuMusic function.
 * Designers can override this function in Blueprint for custom behavior.
 */
void AGM_Menu::PlayMenuMusic()
{
    // Retrieve the custom game instance.
    if (UGI_Template* GameInstance = Cast<UGI_Template>(GetGameInstance()))
    {
        // Play the menu music using the game instance.
        GameInstance->PlayMenuMusic();
    }
}