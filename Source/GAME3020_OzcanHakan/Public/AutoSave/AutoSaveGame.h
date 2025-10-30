// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AutoSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GAME3020_OZCANHAKAN_API UAutoSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Save Data")
    int32 JumpCount;

    UPROPERTY(VisibleAnywhere, Category = "Save Data")
    int32 ButtonClickCount;

    UPROPERTY(VisibleAnywhere, Category = "Save Data")
    int32 ObjectsDestroyedCount;

    UAutoSaveGame()
        : JumpCount(0), ButtonClickCount(0), ObjectsDestroyedCount(0)
    {
    }
};
