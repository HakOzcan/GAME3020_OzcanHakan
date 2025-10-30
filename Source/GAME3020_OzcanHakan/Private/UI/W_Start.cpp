// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/W_Start.h"

void UW_Start::NativeConstruct()
{
    // Always call the base class NativeConstruct first to follow proper initialization.
    Super::NativeConstruct();

    // Play animations by name. Ensure these animations are set up in the widget blueprint.
    PlayAnimation(TextFade, 0, 0, EUMGSequencePlayMode::Forward);
    PlayAnimation(ActiveElementFade, 0, 0, EUMGSequencePlayMode::PingPong);
}
