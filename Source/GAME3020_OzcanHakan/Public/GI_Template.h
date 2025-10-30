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

private:
    // UI Data assets for different platforms (Xbox, PS5, Switch).
    UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
    class UUIDataAsset* XboxUIDataAsset;

    UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
    class UUIDataAsset* PS5UIDataAsset;

    UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
    class UUIDataAsset* SwitchUIDataAsset;

public:
    // Returns the appropriate UI Data asset based on the current platform.
    UFUNCTION(BlueprintCallable)
    class UUIDataAsset* GetUIDataAsset() const;

private:
    // Audio components for handling background music during gameplay, menu, and start screen.
    UPROPERTY()
    class UAudioComponent* GameplayMusicAudioComponent;

    UPROPERTY()
    class UAudioComponent* MenuMusicAudioComponent;

    UPROPERTY()
    class UAudioComponent* StartScreenMusicAudioComponent;

    // Gameplay music choices for each level.
    UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
    TArray<USoundBase*> GameplayMusicChoices;

    // Current level index (0 to 14). You can update this value via Blueprint when the level changes.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music", meta = (AllowPrivateAccess = "true"))
    int32 CurrentLevelIndex = 0;

    // Sound asset for Menu Music.
    UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
    class USoundBase* MenuMusic;

    // Sound asset for Start Screen Music.
    UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
    class USoundBase* StartScreenMusic;

    // Duration used for fading music in and out.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta = (AllowPrivateAccess = "true"))
    float MusicFadeDuration = 1.0f;

public:
    // Plays the gameplay music track based on the current level index.
    UFUNCTION(BlueprintCallable)
    void PlayGameplayMusic();

    // Stops the gameplay music; can force an immediate stop.
    UFUNCTION(BlueprintCallable)
    void StopGameplayMusic(bool ForceStop = false);

    // Plays the menu music track.
    UFUNCTION(BlueprintCallable)
    void PlayMenuMusic();

    // Stops the menu music; can force an immediate stop.
    UFUNCTION(BlueprintCallable)
    void StopMenuMusic(bool ForceStop = false);

    // Plays the start screen music track.
    UFUNCTION(BlueprintCallable)
    void PlayStartScreenMusic();

    // Stops the start screen music; can force an immediate stop.
    UFUNCTION(BlueprintCallable)
    void StopStartScreenMusic(bool ForceStop = false);

    public:
        UPROPERTY(EditAnywhere, BlueprintReadOnly)
        TMap<TSoftObjectPtr<UWorld>, bool> ChapterLevels;

        UFUNCTION()
        void UnlockChapter(TSoftObjectPtr<UWorld> Chapter);

        UFUNCTION()
        void LoadChapter(TSoftObjectPtr<UWorld> Chapter);

        UFUNCTION()
        TArray<bool> GetChaptersLockStatus();

        UFUNCTION()
        TArray<TSoftObjectPtr<UWorld>> GetChaptersSoftObjPtr();
};
