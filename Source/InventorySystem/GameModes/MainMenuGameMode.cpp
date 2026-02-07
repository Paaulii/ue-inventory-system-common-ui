// // Copyright Paulina Hałatek, All Rights Reserved.


#include "GameModes/MainMenuGameMode.h"
#include "CommonActivatableWidget.h"
#include "UIS_UIManagerSubsystem.h"
#include "UI/UIS_CommonUILayerTags.h"
#include "UI/UIS_GameUIPolicy.h"
#include "UI/UIS_PrimaryGameLayout.h"

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (UUIS_UIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIS_UIManagerSubsystem>())
	{
		if (UUIS_GameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			UUIS_PrimaryGameLayout* RootLayout = Policy->GetRootLayout();

			RootLayout->PushWidgetToLayerStack(UI::Layer::Menu, MainMenuWidgetClass);
		}
	}
}
