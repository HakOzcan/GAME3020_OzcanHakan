#pragma once

#include "CoreMinimal.h"
#include "Player Controller/PC_Base.h"
#include "PC_Start.generated.h"

/**
 * 
 */
UCLASS()
class GAME3020_OZCANHAKAN_API APC_Start : public APC_Base
{
	GENERATED_BODY()

public:
    virtual bool InputKey(const FInputKeyParams& Params) override;

    UPROPERTY(EditDefaultsOnly)
    const TSoftObjectPtr<UWorld> NextLevel;
};
