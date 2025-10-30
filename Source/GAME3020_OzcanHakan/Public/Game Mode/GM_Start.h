// GM_Start.h
// Game Mode class used for the start screen.
// Inherits from AGM_Base and sets up the start screen-specific classes.

#pragma once

#include "CoreMinimal.h"
#include "Game Mode/GM_Base.h"
#include "GM_Start.generated.h"

/**
 * AGM_Start
 *
 * This game mode is used for the start screen. It creates local players for each
 * available player index and triggers the start screen music.
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AGM_Start : public AGM_Base
{
	GENERATED_BODY()

public:
    /** Constructor */
    AGM_Start();

    /**
     * StartPlay: Called when the start mode begins play.
     *
     * It creates local players based on the maximum allowed player index and
     * triggers the start screen music.
     */
    virtual void StartPlay() override;

    /**
     * BlueprintNativeEvent for playing start screen music.
     * This function can be overridden in Blueprints to provide custom behavior.
     * If not overridden, the default C++ implementation will be used.
     */
    UFUNCTION(BlueprintNativeEvent, Category = "Audio")
    void PlayStartScreenMusic();
    virtual void PlayStartScreenMusic_Implementation();
};
