// HUD_Menu.h
// HUD for the main menu. Designers can override the setup logic in Blueprint.

#pragma once

#include "CoreMinimal.h"
#include "HUD/HUD_Base.h"
#include "HUD_Menu.generated.h"

/**
 * AHUD_Menu
 *
 * This HUD is used for the main menu.
 * The setup logic is exposed via a BlueprintNativeEvent so that designers can customize it.
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AHUD_Menu : public AHUD_Base
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    // BlueprintNativeEvent for setting up the menu HUD.
    UFUNCTION(BlueprintNativeEvent, Category = "HUD")
    void SetupMenuHUD();
    virtual void SetupMenuHUD_Implementation();
};
