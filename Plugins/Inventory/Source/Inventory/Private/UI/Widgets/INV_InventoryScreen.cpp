#include "UI/Widgets/INV_InventoryScreen.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
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

void UINV_InventoryScreen::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_InventoryViewModel* InventoryVM = UIManager.GetViewModel<UINV_InventoryViewModel>();
	MVVMView->SetViewModel(FName("InventoryViewModel"), InventoryVM);
	CachedInventoryVM = InventoryVM;

	UINV_SelectionViewModel* SelectionVM = UIManager.GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_PlayerStatViewModel* PlayerStatVM = UIManager.GetViewModel<UINV_PlayerStatViewModel>();
	MVVMView->SetViewModel(FName("PlayerStatViewModel"), PlayerStatVM);
	CachedPlayerStatVM = PlayerStatVM;
}

void UINV_InventoryScreen::ClearViewModelsCache()
{
	MVVMView->SetViewModel(FName("InventoryViewModel"), nullptr);
	MVVMView->SetViewModel(FName("SelectionViewModel"), nullptr);
	MVVMView->SetViewModel(FName("PlayerStatViewModel"), nullptr);

	CachedInventoryVM = nullptr;
	CachedSelectionVM = nullptr;
	CachedPlayerStatVM = nullptr;
}
