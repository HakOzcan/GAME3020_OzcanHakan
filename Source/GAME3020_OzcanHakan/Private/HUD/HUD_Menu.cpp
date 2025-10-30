// HUD_Menu.cpp
// Implementation of the main menu HUD.

#include "HUD/HUD_Menu.h"

void AHUD_Menu::BeginPlay()
{
    Super::BeginPlay();
    SetupMenuHUD();
}

void AHUD_Menu::SetupMenuHUD_Implementation()
{
    // Default implementation does nothing.
    // Designers can override this in Blueprint to implement custom menu HUD logic.
}
