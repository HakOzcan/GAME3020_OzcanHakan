// HUD_Game.cpp
// Implementation of the gameplay HUD.

#include "HUD/HUD_Game.h"
#include "Blueprint/UserWidget.h"

void AHUD_Game::BeginPlay()
{
    Super::BeginPlay();
    SetupGameHUD();
}

void AHUD_Game::SetupGameHUD_Implementation()
{
    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }
}

void AHUD_Game::DisplayGameHUD()
{
    if (HUDWidget)
    {
        HUDWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void AHUD_Game::HideGameHUD()
{
    if (HUDWidget)
    {
        HUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}