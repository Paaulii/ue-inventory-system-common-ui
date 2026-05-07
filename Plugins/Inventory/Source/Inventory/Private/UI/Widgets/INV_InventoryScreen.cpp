#include "UI/Widgets/INV_InventoryScreen.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_InventoryScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UINV_InventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	TArray<UINV_CategoryViewModel*> Categories = CachedInventoryVM->GetCategories();
	if (Categories.Num() > 0)
	{
		CachedSelectionVM->SetSelectedCategory(CachedInventoryVM->GetCategories()[0]);
	}
}

void UINV_InventoryScreen::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_InventoryViewModel* InventoryVM = UIManager.GetViewModel<UINV_InventoryViewModel>();
	checkf(InventoryVM, TEXT("UIManager cannot find InventoryViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("InventoryViewModel"), InventoryVM);
	CachedInventoryVM = InventoryVM;

	UINV_SelectionViewModel* SelectionVM = UIManager.GetViewModel<UINV_SelectionViewModel>();
	checkf(SelectionVM, TEXT("UIManager cannot find SelectionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
	CachedSelectionVM = SelectionVM;
	
	UINV_PlayerStatViewModel* PlayerStatVM = UIManager.GetViewModel<UINV_PlayerStatViewModel>();
	checkf(PlayerStatVM, TEXT("UIManager cannot find PlayerStatViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("PlayerStatViewModel"), PlayerStatVM);
	CachedPlayerStatVM = PlayerStatVM;
}
