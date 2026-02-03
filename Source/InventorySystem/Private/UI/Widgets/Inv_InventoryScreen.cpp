// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/Inv_InventoryScreen.h"
#include "Data/InventoryData.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/Widgets/CategoryTabs.h"
#include "View/MVVMView.h"

void UInv_InventoryScreen::CacheViewModels(UUIManagerSubsystem* UIManager)
{
	UInventoryViewModel* InventoryVM = UIManager->GetInventoryVM();
	MVVMView->SetViewModel("InventoryViewModel", InventoryVM);
	CachedInventoryVM = InventoryVM;
}

void UInv_InventoryScreen::ClearViewModelsCache()
{
	MVVMView->SetViewModel("InventoryViewModel", nullptr);
}

void UInv_InventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (!bIsDataDebugInitialized)
	{
		CachedInventoryVM->RebuildInventory(DebugData->InventoryData);
		bIsDataDebugInitialized = true;
	}
}
