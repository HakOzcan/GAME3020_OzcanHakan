// HUD_Start.h
// HUD for the start screen. This HUD creates and manages the start screen widget.

#pragma once

#include "CoreMinimal.h"
#include "HUD/HUD_Base.h"
#include "HUD_Start.generated.h"

/**
 * AHUD_Start
 *
 * This HUD is used for the start screen.
 * The widget creation logic is exposed via a BlueprintNativeEvent so that designers can override it.
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AHUD_Start : public AHUD_Base
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    // BlueprintNativeEvent for setting up the start screen.
    UFUNCTION(BlueprintNativeEvent, Category = "HUD")
    void SetupStartHUD();
    virtual void SetupStartHUD_Implementation();

protected:
    // The widget class for the start screen. Set this in the editor.
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> StartScreenClass;
};
