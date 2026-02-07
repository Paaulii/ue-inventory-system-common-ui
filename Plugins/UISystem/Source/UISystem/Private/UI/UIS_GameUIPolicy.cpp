#include "UI/UIS_GameUIPolicy.h"

#include "Blueprint/UserWidget.h"
#include "Player/UIS_LocalPlayer.h"
#include "UI/UIS_PrimaryGameLayout.h"

void UUIS_GameUIPolicy::NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer)
{
	CreateLayoutWidget(LocalPlayer);
}

void UUIS_GameUIPolicy::CreateLayoutWidget(UUIS_LocalPlayer* LocalPlayer)
{
	if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld()))
	{
		RootLayout = CreateWidget<UUIS_PrimaryGameLayout>(PlayerController, LayoutClass);
		AddLayoutToViewport(LocalPlayer, RootLayout);
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(RootLayout->TakeWidget()); 
		PlayerController->SetInputMode(InputMode);
		return;
	}
	
	LocalPlayer->OnPlayerControllerSet.AddWeakLambda(
		this, [this](UUIS_LocalPlayer* LocalPlayer, APlayerController* PlayerController)
		{
			if (RootLayout != nullptr)
			{
				RemoveLayoutFromViewport(RootLayout);
			}
			CreateLayoutWidget(LocalPlayer);
		});
}

void UUIS_GameUIPolicy::AddLayoutToViewport(UUIS_LocalPlayer* LocalPlayer, UUIS_PrimaryGameLayout* Layout)
{
	Layout->AddToViewport();
	OnRootLayoutAddedToViewport(LocalPlayer, Layout);
}

void UUIS_GameUIPolicy::OnRootLayoutAddedToViewport(UUIS_LocalPlayer* LocalPlayer, UUIS_PrimaryGameLayout* Layout)
{
#if WITH_EDITOR
	if (GIsEditor && LocalPlayer->IsPrimaryPlayer())
	{
		// So our controller will work in PIE without needing to click in the viewport
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
	}
#endif
}

void UUIS_GameUIPolicy::RemoveLayoutFromViewport(UUIS_PrimaryGameLayout* Layout)
{
	TWeakPtr<SWidget> LayoutSlateWidget = Layout->GetCachedWidget();
	if (LayoutSlateWidget.IsValid())
	{
		Layout->RemoveFromParent();
	}
}

void UUIS_GameUIPolicy::NotifyPlayerDestroyed(UUIS_LocalPlayer* LocalPlayer)
{
	LocalPlayer->OnPlayerControllerSet.RemoveAll(this);
	RemoveLayoutFromViewport(RootLayout);
}
