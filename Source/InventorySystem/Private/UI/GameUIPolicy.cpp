#include "UI/GameUIPolicy.h"

#include "Blueprint/UserWidget.h"
#include "Player/CommonLocalPlayer.h"
#include "UI/PrimaryGameLayout.h"

void UGameUIPolicy::NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer)
{
	CreateLayoutWidget(LocalPlayer);
}

void UGameUIPolicy::CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer)
{
	if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld()))
	{
		RootLayout = CreateWidget<UPrimaryGameLayout>(PlayerController, LayoutClass);
		AddLayoutToViewport(LocalPlayer, RootLayout);
		return;
	}
	
	LocalPlayer->OnPlayerControllerSet.AddWeakLambda(
		this, [this](UCommonLocalPlayer* LocalPlayer, APlayerController* PlayerController)
		{
			if (RootLayout != nullptr)
			{
				RemoveLayoutFromViewport(RootLayout);
			}
			CreateLayoutWidget(LocalPlayer);
		});
}

void UGameUIPolicy::AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout)
{
	Layout->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
	Layout->AddToPlayerScreen();
	OnRootLayoutAddedToViewport(LocalPlayer, Layout);
}

void UGameUIPolicy::OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout)
{
#if WITH_EDITOR
	if (GIsEditor && LocalPlayer->IsPrimaryPlayer())
	{
		// So our controller will work in PIE without needing to click in the viewport
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
	}
#endif
}

void UGameUIPolicy::RemoveLayoutFromViewport(UPrimaryGameLayout* Layout)
{
	TWeakPtr<SWidget> LayoutSlateWidget = Layout->GetCachedWidget();
	if (LayoutSlateWidget.IsValid())
	{
		Layout->RemoveFromParent();
	}
}

void UGameUIPolicy::NotifyPlayerDestroyed(UCommonLocalPlayer* LocalPlayer)
{
	LocalPlayer->OnPlayerControllerSet.RemoveAll(this);
	RemoveLayoutFromViewport(RootLayout);
}
