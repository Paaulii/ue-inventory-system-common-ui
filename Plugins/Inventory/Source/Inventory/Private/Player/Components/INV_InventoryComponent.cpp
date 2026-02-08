// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/Components/INV_InventoryComponent.h"

#include "UIS_UIManagerSubsystem.h"
#include "UI/UIS_CommonUILayerTags.h"
#include "UI/UIS_GameUIPolicy.h"
#include "UI/UIS_PrimaryGameLayout.h"
#include "UI/Widgets/INV_InventoryScreen.h"

void UINV_InventoryComponent::ToggleInventory()
{
	SetInventoryVisible(!bInventoryMenuOpen);
}

void UINV_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningController = Cast<APlayerController>(GetOwner());
}

void UINV_InventoryComponent::SetInventoryVisible(bool bIsVisible)
{
	if (bIsVisible)
	{
		OwningController->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		OwningController->SetInputMode(FInputModeGameOnly());
	}

	OwningController->SetShowMouseCursor(bIsVisible);

	bInventoryMenuOpen = bIsVisible;

	if (!bIsVisible)
	{
		return;
	}

	RequestShowInventory();
}

void UINV_InventoryComponent::RequestShowInventory()
{
	UUIS_UIManagerSubsystem* UIManager = OwningController->GetGameInstance()->GetSubsystem<UUIS_UIManagerSubsystem>();

	if (!UIManager)
	{
		return;
	}

	UUIS_GameUIPolicy* Policy = UIManager->GetCurrentUIPolicy();
	if (!Policy)
	{
		return;
	}

	UUIS_PrimaryGameLayout* RootLayout = Policy->GetRootLayout();
	if (!RootLayout)
	{
		return;
	}

	UCommonActivatableWidget* WidgetToActivate = RootLayout->PushWidgetToLayerStack(UI::Layer::GameMenu, InventoryClass);

	if (!bIsBindToInventoryOnDeactivated)
		if (UINV_InventoryScreen* InventoryScreen = Cast<UINV_InventoryScreen>(WidgetToActivate))
		{
			bIsBindToInventoryOnDeactivated = true;
			InventoryScreen->OnDeactivated().AddLambda([this, InventoryScreen]()
			{
				SetInventoryVisible(false);
				InventoryScreen->OnDeactivated().RemoveAll(this);
				bIsBindToInventoryOnDeactivated = false;
			});
		}
}
