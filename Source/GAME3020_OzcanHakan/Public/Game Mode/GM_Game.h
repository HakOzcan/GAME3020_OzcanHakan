// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game Mode/GM_Base.h"
#include "GM_Game.generated.h"

/**
 * 
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AGM_Game : public AGM_Base
{
	GENERATED_BODY()

public:
    /** Constructor */
    AGM_Game();

    /**
     * StartPlay: Called when the game mode begins play.
     *
     * This function performs the following:
     *  - Retrieves our custom game instance.
     *  - Creates a player controller if a valid controller ID is available.
     *  - Sets the input mode to Game Only.
     *  - Plays the gameplay music.
     *  - Triggers a Blueprint event to handle the gameplay-specific logic.
     */
    virtual void StartPlay() override;

    /**
     * BlueprintNativeEvent to initiate gameplay logic.
     *
     * Designers can override this event in Blueprint to implement:
     *  - A timer counting down.
     *  - Spawning or managing collectible objects.
     *  - Win/lose conditions based on whether the player collects required objects before time runs out.
     *
     * The default C++ implementation does nothing.
     */
    UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
    void BeginGameplayLogic();
    virtual void BeginGameplayLogic_Implementation();
};
