// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player Controller/PC_Base.h"
#include "PC_Game.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class GAME3020_OZCANHAKAN_API APC_Game : public APC_Base
{
    GENERATED_BODY()
protected:

    /** Input Mapping Context to be used for player input */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* InputMappingContext;

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
};
