// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Base.generated.h"

/**
 * AGM_Base
 *
 * This is the base game mode that other game modes (gameplay, menu, start, etc.) inherit from.
 * It sets default classes for the player controller and HUD.
 */
UCLASS()
class GAME3020_OZCANHAKAN_API AGM_Base : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	AGM_Base();
};
