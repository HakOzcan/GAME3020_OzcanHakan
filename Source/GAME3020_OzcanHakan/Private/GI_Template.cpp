// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Template.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "MyBlueprintFunctionLibrary.h"

void UGI_Template::Init()
{
    Super::Init();

    // Setup the ticker to call the Tick() function every frame.
    FTickerDelegate TickDelegate = FTickerDelegate::CreateUObject(this, &UGI_Template::Tick);
    TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

    // Bind to controller connection/disconnection events.
    IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &UGI_Template::OnControllerChanged);
}

/**
 * Shutdown the Game Instance.
 * - Removes the ticker delegate.
 */
void UGI_Template::Shutdown()
{
    Super::Shutdown();
    FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

/**
 * Tick function called every frame.
 */
bool UGI_Template::Tick(float DeltaTime)
{
    return true;
}

void UGI_Template::SetActiveControllerID(int32 ControllerID)
{
    ActiveControllerId = ControllerID;
}

/**
 * Returns the active controller ID.
 */
int32 UGI_Template::GetActiveControllerID()
{
    return ActiveControllerId;
}

/**
 * Called when a controller's connection state changes.
 * - If the active controller is affected, pauses/unpauses the game and shows/hides a disconnect widget.
 */
void UGI_Template::OnControllerChanged(EInputDeviceConnectionState connectionState, FPlatformUserId userID, FInputDeviceId inputDeviceID)
{
    // If the changed controller is the currently active one, handle game pause/unpause and widget display.
    if (GetActiveControllerID() == inputDeviceID.GetId())
    {
        if (APlayerController* ActivePC = UMyBlueprintFunctionLibrary::GetActivePlayerController(this))
        {
            if (connectionState == EInputDeviceConnectionState::Connected)
            {
                // If the active controller has reconnected, unpause the game if it was paused.
                if (bDidControllerDisconnectPauseGame)
                {
                    UGameplayStatics::SetGamePaused(this, false);
                    bDidControllerDisconnectPauseGame = false;
                }
                // // Remove the controller disconnected widget from the viewport.
                // W_Controller_Disconnected->RemoveFromParent();
            }
            else // Controller disconnected
            {
                // if (W_Controller_DisconnectedClass)
                // {
                //     // Pause the game if not already paused.
                //     if (!UGameplayStatics::IsGamePaused(this))
                //     {
                //         bDidControllerDisconnectPauseGame = true;
                //         UGameplayStatics::SetGamePaused(this, true);
                //     }
                //     // Create and add the disconnect widget to notify the user.
                //     W_Controller_Disconnected = CreateWidget<UW_Controller_Disconnected>(ActivePC, W_Controller_DisconnectedClass);
                //     W_Controller_Disconnected->AddToViewport();
                // }
            }
        }
    }
}
