// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/W_Controller_Disconnected.h"
#include "GI_Template.generated.h"

/**
 * UGI_Template
 *
 * This Game Instance class is responsible for managing game-wide systems such as input handling, loading screens,
 * UI data assets, and background music for various game states (gameplay, menu, and start screen).
 */
UCLASS()
class GAME3020_OZCANHAKAN_API UGI_Template : public UGameInstance
{
    GENERATED_BODY()

private:
    // Handle for the ticker delegate that calls Tick() every frame.
    FTSTicker::FDelegateHandle TickDelegateHandle;

    // Stores the currently active controller ID.
    int32 ActiveControllerId = -1;

public:
    // Maximum number of controllers supported.
    static const int32 MAX_CONTROLLERS = 4;

    // Overrides the default GameInstance initialization.
    virtual void Init() override;

    // Overrides the default GameInstance shutdown.
    virtual void Shutdown() override;

    // Called every frame.
    bool Tick(float DeltaSeconds);

    // Sets the active controller ID.
    void SetActiveControllerID(int32 ControllerID);

    // Returns the current active controller ID.
    int32 GetActiveControllerID();

public:
    // Called when a new map is about to be loaded; begins the loading screen process.
    UFUNCTION()
    virtual void BeginLoadingScreen(const FString& MapName);

    // Called after a map has been loaded; ends the loading screen process.
    UFUNCTION()
    virtual void EndLoadingScreen(UWorld* InLoadedWorld);

private:
    // Flag to indicate if the game was paused because the active controller disconnected.
    bool bDidControllerDisconnectPauseGame = false;

    // Widget class used to show a disconnected controller message.
    UPROPERTY(EditAnywhere, Category = "Controller Disconnected Widget")
    TSubclassOf<class UW_Controller_Disconnected> W_Controller_DisconnectedClass;

    // Widget class used for save notifications.
    UPROPERTY(EditDefaultsOnly, Category = "Widget")
    TSubclassOf<UUserWidget> SaveNotificationWidgetClass;

    // Instance of the controller disconnected widget.
    UPROPERTY()
    class UW_Controller_Disconnected* W_Controller_Disconnected;

    // Called when a controller connection state changes (connect/disconnect).
    UFUNCTION()
    void OnControllerChanged(EInputDeviceConnectionState connectionState, FPlatformUserId userID, FInputDeviceId inputDeviceID);
};
