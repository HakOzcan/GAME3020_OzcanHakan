// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "C_Game.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class GAME3020_OZCANHAKAN_API AC_Game : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

private:
    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    /** Grab Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* GrabAction;

public:
    /** Pause Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* PauseAction;

    // Some platforms (e.g. Switch) differ in which button acts as "Back"
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* BackActionRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* BackActionBottom;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pause Menu", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

    UPROPERTY()
    class UUserWidget* PauseMenuWidget;
public:
    AC_Game();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

protected:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable)
    void Pause();

    void Grab();
    void Release();

public:
    UFUNCTION(BlueprintCallable)
    void Back();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

