#include "AutoSave/AutoSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void UAutoSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // Load previous save data if available
    LoadGame();
}

void UAutoSaveSubsystem::Deinitialize()
{
    GetWorld()->GetTimerManager().ClearTimer(HideWidgetTimerHandle);
    Super::Deinitialize();
}

void UAutoSaveSubsystem::IncrementJumpCount()
{
    JumpCount++;

    // Save every time jump count is a multiple of 10
    if (JumpCount % 10 == 0)
    {
        if (SaveGame())
        {
            ShowSaveNotificationWidget();
        }
    }
}

void UAutoSaveSubsystem::IncrementButtonClickCount()
{
    ButtonClickCount++;

    // Save every time click count is a multiple of 10
    if (ButtonClickCount % 10 == 0)
    {
        if (SaveGame())
        {
            ShowSaveNotificationWidget();
        }
    }
}

bool UAutoSaveSubsystem::SaveGame()
{
    UAutoSaveGame* SaveGameInstance = Cast<UAutoSaveGame>(UGameplayStatics::CreateSaveGameObject(UAutoSaveGame::StaticClass()));
    if (!SaveGameInstance) return false;

    SaveGameInstance->JumpCount = JumpCount;
    SaveGameInstance->ButtonClickCount = ButtonClickCount;
    SaveGameInstance->ObjectsDestroyedCount = ObjectsDestroyedCount;

    return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}

void UAutoSaveSubsystem::LoadGame()
{
    if (UAutoSaveGame* LoadedGame = Cast<UAutoSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
    {
        JumpCount = LoadedGame->JumpCount;
        ButtonClickCount = LoadedGame->ButtonClickCount;
        ObjectsDestroyedCount = LoadedGame->ObjectsDestroyedCount;
    }
    else
    {
        JumpCount = 0;
        ButtonClickCount = 0;
        ObjectsDestroyedCount = 0;
    }
}

void UAutoSaveSubsystem::ShowSaveNotificationWidget()
{
    if (SaveNotificationWidgetClass && !ActiveSaveNotificationWidget)
    {
        ActiveSaveNotificationWidget = CreateWidget<UUserWidget>(GetWorld(), SaveNotificationWidgetClass);
        if (ActiveSaveNotificationWidget)
        {
            ActiveSaveNotificationWidget->AddToViewport();
            GetWorld()->GetTimerManager().SetTimer(HideWidgetTimerHandle, this, &UAutoSaveSubsystem::HideSaveNotificationWidget, 2.0f, false);
        }
    }
}

void UAutoSaveSubsystem::HideSaveNotificationWidget()
{
    if (ActiveSaveNotificationWidget)
    {
        ActiveSaveNotificationWidget->RemoveFromParent();
        ActiveSaveNotificationWidget = nullptr;
    }
}

void UAutoSaveSubsystem::IncrementObjectsDestroyedCount()
{
    ObjectsDestroyedCount++;

    // Save every time an object is destroyed
    if (SaveGame())
    {
        ShowSaveNotificationWidget();
    }
}