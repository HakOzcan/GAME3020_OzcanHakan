#include "Player Controller/PC_Start.h"
#include "MyBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

bool APC_Start::InputKey(const FInputKeyParams& Params)
{
    if (Params.Event == IE_Pressed && Params.IsGamepad())
    {
        UMyBlueprintFunctionLibrary::SetActiveControllerID(GetWorld(), GetLocalPlayer()->GetLocalPlayerIndex());
        UMyBlueprintFunctionLibrary::RemoveAllPlayers(GetWorld());

        ensure(!NextLevel.IsNull());
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextLevel);
    }
    return Super::InputKey(Params);
}