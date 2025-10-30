// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Template.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "MyBlueprintFunctionLibrary.h"
#include "CustomGameViewportClient.h"
#include "Components/AudioComponent.h"
#include "LoadingScreenModule.h"
#include "AutoSave/AutoSaveSubsystem.h"

void UGI_Template::Init()
{
    Super::Init();

    // Setup the ticker to call the Tick() function every frame.
    FTickerDelegate TickDelegate = FTickerDelegate::CreateUObject(this, &UGI_Template::Tick);
    TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

    // Bind to controller connection/disconnection events.
    IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &UGI_Template::OnControllerChanged);

    // Bind functions to execute before and after a map is loaded.
    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UGI_Template::BeginLoadingScreen);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGI_Template::EndLoadingScreen);

    // Get and configure the AutoSave subsystem if available.
    UAutoSaveSubsystem* AutoSaveSubsystem = GetSubsystem<UAutoSaveSubsystem>();
    if (AutoSaveSubsystem)
    {
        AutoSaveSubsystem->SaveNotificationWidgetClass = SaveNotificationWidgetClass;
    }
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
 * Returns the UI Data asset based on the current platform.
 * - For PS5, returns PS5UIDataAsset.
 * - For SWITCH, returns SwitchUIDataAsset.
 * - Otherwise, returns XboxUIDataAsset.
 */
UUIDataAsset* UGI_Template::GetUIDataAsset() const
{
    FString PlatformName = UGameplayStatics::GetPlatformName();

    if (PlatformName == "PS5")
    {
        return PS5UIDataAsset;
    }
    else if (PlatformName == "SWITCH")
    {
        return SwitchUIDataAsset;
    }
    else
    {
        return XboxUIDataAsset;
    }
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
                if (W_Controller_DisconnectedClass)
                {
                    // Pause the game if not already paused.
                    if (!UGameplayStatics::IsGamePaused(this))
                    {
                        bDidControllerDisconnectPauseGame = true;
                        UGameplayStatics::SetGamePaused(this, true);
                    }
                    // Create and add the disconnect widget to notify the user.
                    W_Controller_Disconnected = CreateWidget<UW_Controller_Disconnected>(ActivePC, W_Controller_DisconnectedClass);
                    W_Controller_Disconnected->AddToViewport();
                }
            }
        }
    }
}

/**
 * Begins the loading screen process.
 * - Fades the screen to black.
 * - Depending on the map name, may start an in-game loading screen.
 */
void UGI_Template::BeginLoadingScreen(const FString& InMapName)
{
    // Fade in to black using the game viewport client.
    const UWorld* World = GetWorld();
    if (World)
    {
        UCustomGameViewportClient* GameViewportClient = Cast<UCustomGameViewportClient>(World->GetGameViewport());
        if (GameViewportClient)
        {
            GameViewportClient->Fade(true);
        }
    }

    // Check if the map is a frontend screen (determined by map name starting with "L_").
    if (InMapName.Contains("L_"))
    {
        // Frontend screens do not require a loading screen.
    }
    else
    {
        // For gameplay screens, start the in-game loading screen using the LoadingScreenModule.
        ILoadingScreenModule* LoadingScreenModule =
            FModuleManager::LoadModulePtr<ILoadingScreenModule>("LoadingScreenModule");
        if (LoadingScreenModule != NULL)
        {
            LoadingScreenModule->StartInGameLoadingScreen();
        }
    }
}

/**
 * Ends the loading screen process.
 * - Fades the screen from black.
 */
void UGI_Template::EndLoadingScreen(UWorld* InLoadedWorld)
{
    // Fade out from black using the game viewport client.
    const UWorld* World = GetWorld();
    if (World)
    {
        UCustomGameViewportClient* GameViewportClient = Cast<UCustomGameViewportClient>(World->GetGameViewport());
        if (GameViewportClient)
        {
            GameViewportClient->Fade(false);
        }
    }
}

/**
 * Plays the gameplay music corresponding to the current level.
 * - Stops menu and start screen music first.
 * - Chooses a track from GameplayMusicChoices based on CurrentLevelIndex.
 */
void UGI_Template::PlayGameplayMusic()
{
    StopMenuMusic();
    StopStartScreenMusic();

    if (GameplayMusicChoices.IsValidIndex(CurrentLevelIndex))
    {
        USoundBase* SelectedMusic = GameplayMusicChoices[CurrentLevelIndex];

        if (GameplayMusicAudioComponent)
        {
            if (!GameplayMusicAudioComponent->IsPlaying())
            {
                GameplayMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
            }
        }
        else
        {
            GameplayMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, SelectedMusic);

            if (GameplayMusicAudioComponent)
            {
                GameplayMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
            }
        }
    }
}

/**
 * Stops the gameplay music.
 * - If ForceStop is true, stops immediately; otherwise, fades out the music.
 */
void UGI_Template::StopGameplayMusic(bool ForceStop)
{
    if (GameplayMusicAudioComponent && GameplayMusicAudioComponent->IsPlaying())
    {
        if (ForceStop)
        {
            GameplayMusicAudioComponent->Stop();
        }
        else
        {
            GameplayMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
        }
    }
}

/**
 * Plays the menu music.
 * - Stops gameplay and start screen music to avoid audio conflicts.
 * - Either fades in an existing menu music audio component or spawns a new one.
 */
void UGI_Template::PlayMenuMusic()
{
    StopGameplayMusic();
    StopStartScreenMusic();

    if (MenuMusicAudioComponent)
    {
        if (!MenuMusicAudioComponent->IsPlaying())
        {
            MenuMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
        }
    }
    else
    {
        if (MenuMusic)
        {
            MenuMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, MenuMusic, 1, 1, 0, nullptr, true, true);

            if (MenuMusicAudioComponent)
            {
                MenuMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
            }
        }
    }
}

/**
 * Stops the menu music.
 * - If ForceStop is true, stops immediately; otherwise, fades out the music.
 */
void UGI_Template::StopMenuMusic(bool ForceStop)
{
    if (MenuMusicAudioComponent && MenuMusicAudioComponent->IsPlaying())
    {
        if (ForceStop)
        {
            MenuMusicAudioComponent->Stop();
        }
        else
        {
            MenuMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
        }
    }
}

/**
 * Plays the start screen music.
 * - Stops gameplay and menu music first.
 * - Fades in or spawns the start screen music audio component.
 */
void UGI_Template::PlayStartScreenMusic()
{
    StopGameplayMusic();
    StopMenuMusic();

    if (StartScreenMusicAudioComponent)
    {
        if (!StartScreenMusicAudioComponent->IsPlaying())
        {
            StartScreenMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
        }
    }
    else
    {
        if (StartScreenMusic)
        {
            StartScreenMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, StartScreenMusic);

            if (StartScreenMusicAudioComponent)
            {
                StartScreenMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
            }
        }
    }
}

/**
 * Stops the start screen music.
 * - If ForceStop is true, stops immediately; otherwise, fades out the music.
 */
void UGI_Template::StopStartScreenMusic(bool ForceStop)
{
    if (StartScreenMusicAudioComponent && StartScreenMusicAudioComponent->IsPlaying())
    {
        if (ForceStop)
        {
            StartScreenMusicAudioComponent->Stop();
        }
        else
        {
            StartScreenMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
        }
    }
}

void UGI_Template::UnlockChapter(TSoftObjectPtr<UWorld> Chapter)
{
    const UWorld* World = GetWorld();
    if (World)
    {
        if (ChapterLevels.Contains(Chapter))
        {
            ChapterLevels[Chapter] = true;
        }
    }
}

void UGI_Template::LoadChapter(TSoftObjectPtr<UWorld> Chapter)
{
    UWorld* World = GetWorld();
    if (World)
    {
        if (ChapterLevels.Contains(Chapter) && ChapterLevels[Chapter])
        {
            UGameplayStatics::OpenLevelBySoftObjectPtr(World, Chapter);
        }
    }
}

TArray<bool> UGI_Template::GetChaptersLockStatus()
{
    TArray<bool> ChaptersStatus;
    ChapterLevels.GenerateValueArray(ChaptersStatus);
    return ChaptersStatus;
}

TArray<TSoftObjectPtr<UWorld>> UGI_Template::GetChaptersSoftObjPtr()
{
    TArray<TSoftObjectPtr<UWorld>> ChaptersSoftObjPtrs;
    ChapterLevels.GenerateKeyArray(ChaptersSoftObjPtrs);
    return ChaptersSoftObjPtrs;
}
