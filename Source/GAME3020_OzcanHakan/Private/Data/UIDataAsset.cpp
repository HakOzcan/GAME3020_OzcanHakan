#include "Data/UIDataAsset.h"

UTexture2D* UUIDataAsset::GetIcon(EIconType IconType) const
{
    switch (IconType)
    {
    case EIconType::Select:
        return SelectIcon.LoadSynchronous();
    case EIconType::Back:
        return BackIcon.LoadSynchronous();
    default:
        return nullptr;
    }
}