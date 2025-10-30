// HUD_Game.h
// HUD for the gameplay. This HUD manages the gameplay widget and provides functions to display or hide it.

#pragma once

#include "CoreMinimal.h"
#include "HUD/HUD_Base.h"
#include "HUD_Game.generated.h"

/**
 * AHUD_Game
 *
 * This HUD is used during gameplay. It creates and manages the gameplay HUD widget.
 * The widget creation logic is exposed via a BlueprintNativeEvent so that designers can override it.
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AHUD_Game : public AHUD_Base
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

public:
    // Blueprint callable functions to change the widget's visibility.
    UFUNCTION(BlueprintCallable)
    void DisplayGameHUD();

    UFUNCTION(BlueprintCallable)
    void HideGameHUD();

    // BlueprintNativeEvent for setting up the HUD.
    // Designers can override this event in Blueprint to customize widget creation.
    UFUNCTION(BlueprintNativeEvent, Category = "HUD")
    void SetupGameHUD();
    virtual void SetupGameHUD_Implementation();

protected:
    // The widget class to use for the gameplay HUD. Set this in the editor.
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    // The instance of the HUD widget.
    UPROPERTY()
    class UUserWidget* HUDWidget;
};
