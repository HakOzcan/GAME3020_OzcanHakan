// GM_Start.cpp
// Implementation of the start screen game mode.

#include "Game Mode/GM_Start.h"
#include "Player Controller/PC_Start.h"   // Custom start screen player controller
#include "HUD/HUD_Start.h"                // Custom start screen HUD class
#include "MyBlueprintFunctionLibrary.h"   // Provides maximum player index value
#include "Engine/GameInstance.h"
#include "GI_Template.h"                  // Custom Game Instance class

/**
 * Constructor: Sets up the start screen-specific classes.
 */
AGM_Start::AGM_Start()
    : Super()
{
    // Set the custom start screen player controller.
    PlayerControllerClass = APC_Start::StaticClass();

    // Set the custom start screen HUD.
    HUDClass = AHUD_Start::StaticClass();
}

/**
 * StartPlay: Called when the start screen mode begins play.
 *
 * This function performs the following:
 *  - Retrieves the current world and game instance.
 *  - Creates local players for each player ID up to the maximum allowed.
 *  - Triggers the start screen music via a BlueprintNativeEvent.
 */
void AGM_Start::StartPlay()
{
    Super::StartPlay();

    // Retrieve the current world and its game instance.
    UWorld* CurrentWorld = GetWorld();
    UGameInstance* GameInstance = CurrentWorld->GetGameInstance();

    // Loop through all potential player IDs and create a local player for each.
    for (int32 PlayerID = 0; PlayerID <= UMyBlueprintFunctionLibrary::GetLastMaxPlayerIndex(); ++PlayerID)
    {
        FString Error;
        // The third parameter (true) forces creation even if one already exists.
        ULocalPlayer* LocalPlayer = GameInstance->CreateLocalPlayer(PlayerID, Error, true);
    }

    // Call the BlueprintNativeEvent to handle start screen music playback.
    PlayStartScreenMusic();
}

/**
 * Default implementation for PlayStartScreenMusic.
 * This implementation attempts to retrieve our custom game instance and play the start screen music.
 * Designers can override this function in Blueprint for custom behavior.
 */
void AGM_Start::PlayStartScreenMusic_Implementation()
{
    // Retrieve the game instance and cast it to our custom type.
    if (UGI_Template* GameInstanceRef = Cast<UGI_Template>(GetWorld()->GetGameInstance()))
    {
        GameInstanceRef->PlayStartScreenMusic();
    }
}