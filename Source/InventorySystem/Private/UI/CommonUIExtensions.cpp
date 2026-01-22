#include "UI/CommonUIExtensions.h"
#include "GameplayTagContainer.h"
#include "GameUIManagerSubsystem.h"
#include "UI/PrimaryGameLayout.h"
#include "UI/GameUIPolicy.h"
#include "CommonActivatableWidget.h"

// TODO: Apply VM if needed
UCommonActivatableWidget* UCommonUIExtensions::PushContentToLayer(const ULocalPlayer* LocalPlayer,
	FGameplayTag LayerName, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(LocalPlayer) || !ensure(WidgetClass != nullptr))
	{
		return nullptr;
	}

	if (UGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout())
			{
				return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
			}
		}
	}

	return nullptr;
}
