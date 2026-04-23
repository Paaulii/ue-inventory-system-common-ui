#include "GameModes/IS_AutoOpenWidgetGameMode.h"
#include "CommonActivatableWidget.h"
#include "UIS_UIManagerSubsystem.h"
#include "UI/UIS_GameUIPolicy.h"
#include "UI/UIS_PrimaryGameLayout.h"

void AIS_AutoOpenWidgetGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (UUIS_UIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIS_UIManagerSubsystem>())
	{
		if (UUIS_GameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			UUIS_PrimaryGameLayout* RootLayout = Policy->GetRootLayout();

			RootLayout->PushWidgetToLayerStack(LayerStackTag, WidgetToOpenClass);
		}
	}
}
