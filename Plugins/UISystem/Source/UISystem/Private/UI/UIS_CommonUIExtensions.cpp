#include "UI/UIS_CommonUIExtensions.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "UIS_UIManagerSubsystem.h"
#include "UI/UIS_GameUIPolicy.h"
#include "UI/UIS_PrimaryGameLayout.h"

UCommonActivatableWidget* UUIS_CommonUIExtensions::PushContentToLayer(const ULocalPlayer* LocalPlayer,
	FGameplayTag LayerName, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(LocalPlayer) || !ensure(WidgetClass))
	{
		return nullptr;
	}
	
	UUIS_UIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UUIS_UIManagerSubsystem>();
	checkf(UIManager, TEXT("Cannot push UI to root layout. Cannot find UIManagerSubsystem."))
	if (UUIS_GameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
	{
		if (UUIS_PrimaryGameLayout* RootLayout = Policy->GetRootLayout())
		{
			return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
		}
	}

	return nullptr;
}
