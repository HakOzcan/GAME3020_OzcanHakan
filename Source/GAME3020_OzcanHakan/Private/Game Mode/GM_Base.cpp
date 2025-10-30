// GM_Base.cpp
// Implementation of the base game mode class.

#include "Game Mode/GM_Base.h"
#include "Player Controller/PC_Base.h"   // Custom base player controller

/**
 * Constructor: Sets the default classes for the player controller and HUD.
 */
AGM_Base::AGM_Base()
    : Super()
{
    // Set the PlayerControllerClass to our custom PC_Base.
    PlayerControllerClass = APC_Base::StaticClass();
}