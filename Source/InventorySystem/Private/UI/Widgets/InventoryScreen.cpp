// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/InventoryScreen.h"
#include "Data/InventoryData.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "UI/Widgets/CategoryTabs.h"
#include "View/MVVMView.h"


void UInventoryScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UInventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		if (MVVMView)
		{
			MVVMView->SetViewModel("InventoryViewModel", UIManager->GetInventoryVM());
		}

		if (!bIsDataDebugInitialized)
		{
			UIManager->GetInventoryVM()->RebuildInventory(DebugData->InventoryData);
			bIsDataDebugInitialized = true;
		}
	}
	
	NotifyChildWidgetsOnActivated();
}


void UInventoryScreen::NativeOnDeactivated()
{
	if (MVVMView)
	{
		MVVMView->SetViewModel("InventoryViewModel", nullptr);
	}
	
	Super::NativeOnDeactivated();
}

void UInventoryScreen::NotifyChildWidgetsOnActivated() const
{
	CategoryTabs->OnActivated();
}
