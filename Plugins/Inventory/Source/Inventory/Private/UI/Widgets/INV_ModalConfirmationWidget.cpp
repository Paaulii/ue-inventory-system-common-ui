#include "UI/Widgets/INV_ModalConfirmationWidget.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"
void UINV_ModalConfirmationWidget::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager.GetViewModel<UINV_SelectionViewModel>();
	checkf(SelectionVM, TEXT("UIManager cannot find SelectionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_ItemActionViewModel* ItemActionVM = UIManager.GetViewModel<UINV_ItemActionViewModel>();
	checkf(ItemActionVM, TEXT("UIManager cannot find ItemActionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("ItemActionViewModel"), ItemActionVM);
	CachedItemActionVM = ItemActionVM;
}

void UINV_ModalConfirmationWidget::ClearViewModelsCache()
{
	MVVMView->SetViewModel(FName("SelectionViewModel"), nullptr);
	MVVMView->SetViewModel(FName("ItemActionViewModel"), nullptr);
	CachedSelectionVM = nullptr;
	CachedItemActionVM = nullptr;
}

void UINV_ModalConfirmationWidget::VM_SelectedItemChanged(const UINV_ItemViewModel* ItemVM)
{
	if (ItemVM == nullptr)
	{
		return;
	}
	
	ImageIcon->SetBrushFromTexture(ItemVM->GetSmallImage());
}

void UINV_ModalConfirmationWidget::OnConfirmAction()
{
	const UINV_ItemViewModel* ItemViewModel = CachedSelectionVM->GetSelectedItem();

	if (!ItemViewModel)
	{
		return;
	}

	CachedItemActionVM->DelegatePerformAction(ItemViewModel->GetItemIdentification());
}

void UINV_ModalConfirmationWidget::VM_ToggleItemQuantityVisibility(bool bIsSingleItemQuantityAction)
{
	QuantityText->SetVisibility(bIsSingleItemQuantityAction? ESlateVisibility::Collapsed : ESlateVisibility::Visible);	
}