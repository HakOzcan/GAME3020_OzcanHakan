// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Start.generated.h"

/**
 * 
 */
UCLASS()
class GAME3020_OZCANHAKAN_API UW_Start : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> TextFade;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> ActiveElementFade;
};
