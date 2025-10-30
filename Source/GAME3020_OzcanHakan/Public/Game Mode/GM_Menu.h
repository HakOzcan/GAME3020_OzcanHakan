// GM_Menu.h
// Game Mode class used for the main menu.
// Inherits from AGM_Base and sets up the menu-specific player controller and HUD.

#pragma once

#include "CoreMinimal.h"
#include "Game Mode/GM_Base.h"
#include "GM_Menu.generated.h"

/**
 * AGM_Menu
 *
 * This game mode is used for the main menu. It assigns the menu-specific player controller
 * and HUD and triggers the menu music on start.
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AGM_Menu : public AGM_Base
{
	GENERATED_BODY()

public:
    /** Constructor */
    AGM_Menu();

    /**
     * StartPlay: Called when the menu mode begins play.
     * It triggers the menu music via a BlueprintNativeEvent.
     */
    virtual void StartPlay() override;

    void PlayMenuMusic();
};
