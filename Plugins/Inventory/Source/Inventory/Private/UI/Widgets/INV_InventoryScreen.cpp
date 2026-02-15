// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/INV_InventoryScreen.h"
#include "Data/INV_InventoryData.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_InventoryScreen::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_InventoryViewModel* InventoryVM = UIManager->GetViewModel<UINV_InventoryViewModel>();
	MVVMView->SetViewModel("InventoryViewModel", InventoryVM);
	CachedInventoryVM = InventoryVM;

	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
	CachedSelectionVM = SelectionVM;
}

void UINV_InventoryScreen::ClearViewModelsCache()
{
	MVVMView->SetViewModel("InventoryViewModel", nullptr);
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
}

void UINV_InventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (!bIsDataDebugInitialized && CachedInventoryVM)
	{
		CachedInventoryVM->RebuildInventory(DebugData->InventoryData);
		bIsDataDebugInitialized = true;
	}
}