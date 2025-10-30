#include "LoadingScreenModule.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"

struct FLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
    FLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
        : FSlateDynamicImageBrush(InTextureName, InImageSize)
    {
        SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
    }

    virtual void AddReferencedObjects(FReferenceCollector& Collector)
    {
        FSlateBrush::AddReferencedObjects(Collector);
    }

    virtual FString GetReferencerName(void) const
    {
        return "FLoadingScreenBrush";
    }
};

class SIngameLoadingScreen : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SIngameLoadingScreen) {}
        SLATE_ARGUMENT(FName, SelectedTexture)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs)
    {
        FName SelectedTexture = InArgs._SelectedTexture;

        LoadingScreenBrush = MakeShareable(new FLoadingScreenBrush(SelectedTexture, FVector2D(1920, 1080)));

        ChildSlot
            [
                SNew(SOverlay)
                    + SOverlay::Slot()
                    .HAlign(HAlign_Fill)
                    .VAlign(VAlign_Fill)
                    [
                        SNew(SImage)
                            .Image(LoadingScreenBrush.Get())
                    ]
                    + SOverlay::Slot()
                    .HAlign(HAlign_Fill)
                    .VAlign(VAlign_Fill)
                    [
                        SNew(SSafeZone)
                            .VAlign(VAlign_Bottom)
                            .HAlign(HAlign_Right)
                            .Padding(10.0f)
                            .IsTitleSafe(true)
                            [
                                SNew(SThrobber)
                                    .Visibility(this, &SIngameLoadingScreen::GetLoadIndicatorVisibility)
                            ]
                    ]
            ];
    }

private:
    EVisibility GetLoadIndicatorVisibility() const
    {
        return EVisibility::Visible;
    }

    /** loading screen image brush */
    TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FLoadingScreenModule : public ILoadingScreenModule
{
public:
    virtual void StartupModule() override
    {
        // Preload references to loading screen textures
        LoadingTextures = {
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG.LoadingScreenBG"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG1.LoadingScreenBG1"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG2.LoadingScreenBG2"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG3.LoadingScreenBG3"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG4.LoadingScreenBG4"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG5.LoadingScreenBG5"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG6.LoadingScreenBG6"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG7.LoadingScreenBG7"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG8.LoadingScreenBG8"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG9.LoadingScreenBG9"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG10.LoadingScreenBG10"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG11.LoadingScreenBG11"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG12.LoadingScreenBG12"),
            TEXT("/Game/FirstPerson/UI/Assets/LoadingScreenBG13.LoadingScreenBG13")
        };

        for (auto texture : LoadingTextures)
        {
            LoadObject<UObject>(NULL, *texture.ToString());
        }
    }

    virtual bool IsGameModule() const override
    {
        return true;
    }

    virtual void StartInGameLoadingScreen() override
    {
        int32 RandomIndex = FMath::RandRange(0, LoadingTextures.Num() - 1);
        FName SelectedTexture = LoadingTextures[RandomIndex];

        FLoadingScreenAttributes LoadingScreen;
        LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
        LoadingScreen.MinimumLoadingScreenDisplayTime = 5.0f;
        LoadingScreen.WidgetLoadingScreen = SNew(SIngameLoadingScreen).SelectedTexture(SelectedTexture);

        GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
    }
};

IMPLEMENT_GAME_MODULE(FLoadingScreenModule, LoadingScreenModule);
