// HUD_Start.cpp
// Implementation of the start screen HUD.

#include "HUD/HUD_Start.h"
#include "Blueprint/UserWidget.h"

void AHUD_Start::BeginPlay()
{
    Super::BeginPlay();
    SetupStartHUD();
}

void AHUD_Start::SetupStartHUD_Implementation()
{
    ensure(StartScreenClass != nullptr);
    if (StartScreenClass != nullptr)
    {
        UUserWidget* StartScreen = CreateWidget<UUserWidget>(GetWorld(), StartScreenClass);
        if (StartScreen)
        {
            StartScreen->AddToViewport();
        }
    }
}