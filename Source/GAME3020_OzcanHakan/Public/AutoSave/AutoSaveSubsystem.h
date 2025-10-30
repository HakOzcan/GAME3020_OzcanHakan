// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "AutoSave/AutoSaveGame.h"
#include "AutoSaveSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAME3020_OZCANHAKAN_API UAutoSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    void Initialize(FSubsystemCollectionBase& Collection) override;
    void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "AutoSave")
    void IncrementJumpCount();

    UFUNCTION(BlueprintCallable, Category = "AutoSave")
    void IncrementButtonClickCount();

    UFUNCTION(BlueprintCallable, Category = "AutoSave")
    bool SaveGame();

    UFUNCTION(BlueprintCallable, Category = "AutoSave")
    void LoadGame();

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> SaveNotificationWidgetClass;

public:
    UFUNCTION(BlueprintCallable, Category = "AutoSave")
    void IncrementObjectsDestroyedCount();

protected:
    int32 ObjectsDestroyedCount;

protected:
    UPROPERTY()
    UUserWidget* ActiveSaveNotificationWidget;

    int32 JumpCount;
    int32 ButtonClickCount;

    void ShowSaveNotificationWidget();
    void HideSaveNotificationWidget();

private:
    FString SlotName = TEXT("AutoSaveSlot");
    FTimerHandle HideWidgetTimerHandle;
};
