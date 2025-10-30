// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "GI_Template.h"
#include "Kismet/GameplayStatics.h"

int32 UMyBlueprintFunctionLibrary::GetLastMaxPlayerIndex()
{
    return UGI_Template::MAX_CONTROLLERS - 1;
}

void UMyBlueprintFunctionLibrary::SetActiveControllerID(const UObject* WorldContextObject, int32 ControllerID)
{
    UGI_Template* GameInstanceRef = Cast<UGI_Template>(UGameplayStatics::GetGameInstance(WorldContextObject));
    if (GameInstanceRef)
    {
        GameInstanceRef->SetActiveControllerID(ControllerID);
    }
}

int32 UMyBlueprintFunctionLibrary::GetActiveControllerID(const UObject* WorldContextObject)
{
    UGI_Template* GameInstanceRef = Cast<UGI_Template>(UGameplayStatics::GetGameInstance(WorldContextObject));
    if (GameInstanceRef)
    {
        return GameInstanceRef->GetActiveControllerID();
    }
    return -1;  // Return -1 if no valid game instance is found or no controller ID is set.
}

void UMyBlueprintFunctionLibrary::RemoveAllPlayers(const UObject* WorldContextObject)
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerController::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        APlayerController* PC = Cast<APlayerController>(Actor);
        if (PC)
        {
            UGameplayStatics::RemovePlayer(PC, true);
        }
    }
}

APlayerController* UMyBlueprintFunctionLibrary::GetActivePlayerController(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetPlayerControllerFromID(WorldContextObject, GetActiveControllerID(WorldContextObject));
}

ACharacter* UMyBlueprintFunctionLibrary::GetActivePlayerCharacter(const UObject* WorldContextObject)
{
    return GetActivePlayerController(WorldContextObject)->GetCharacter();
}

UUIDataAsset* UMyBlueprintFunctionLibrary::GetUIDataAsset(const UObject* WorldContextObject)
{
    const UGI_Template* GameInstance = Cast<UGI_Template>(UGameplayStatics::GetGameInstance(WorldContextObject));
    if (!GameInstance) return nullptr;
    return GameInstance->GetUIDataAsset();
}

