// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/INV_InventoryScreen.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "View/MVVMView.h"

void UINV_InventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	TArray<UINV_CategoryViewModel*> Categories = CachedInventoryVM->GetCategories();
	if (Categories.Num() > 0)
	{
		CachedSelectionVM->SetSelectedCategory(CachedInventoryVM->GetCategories()[0]);
	}
}

void UINV_InventoryScreen::NativeOnDeactivated()
{
	CachedSelectionVM->SetSelectedCategory(nullptr);
	Super::NativeOnDeactivated();
}

void UINV_InventoryScreen::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_InventoryViewModel* InventoryVM = UIManager->GetViewModel<UINV_InventoryViewModel>();
	MVVMView->SetViewModel("InventoryViewModel", InventoryVM);
	CachedInventoryVM = InventoryVM;

	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_PlayerStatViewModel* PlayerStatVM = UIManager->GetViewModel<UINV_PlayerStatViewModel>();
	MVVMView->SetViewModel("PlayerStatViewModel", PlayerStatVM);
	CachedPlayerStatVM = PlayerStatVM;
}

void UINV_InventoryScreen::ClearViewModelsCache()
{
	MVVMView->SetViewModel("InventoryViewModel", nullptr);
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	MVVMView->SetViewModel("PlayerStatViewModel", nullptr);

	CachedInventoryVM = nullptr;
	CachedSelectionVM = nullptr;
	CachedPlayerStatVM = nullptr;
}
