// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ModalConfirmationWidget.h"

#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"

void UINV_ModalConfirmationWidget::VM_SelectedItemChanged(UINV_ItemViewModel* ItemVM)
{
	Image_Icon->SetBrushFromTexture(ItemVM->GetSmallImage());
}

void UINV_ModalConfirmationWidget::VM_ToggleItemQuantityVisibility(bool bIsSingleItemQuantityAction)
{
	Text_Quantity->SetVisibility(bIsSingleItemQuantityAction? ESlateVisibility::Collapsed : ESlateVisibility::Visible);	
}

void UINV_ModalConfirmationWidget::OnConfirmAction()
{
	UINV_ItemViewModel* ItemViewModel = CachedSelectionVM->GetSelectedItem();

	if (!ItemViewModel)
	{
		return;
	}

	CachedItemActionVM->DelegatePerformAction(ItemViewModel->GetItemIdentification(), ItemViewModel->GetSaveIndex());
}

void UINV_ModalConfirmationWidget::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_ItemActionViewModel* ItemActionVM = UIManager->GetViewModel<UINV_ItemActionViewModel>();
	MVVMView->SetViewModel("ItemActionViewModel", ItemActionVM);
	CachedItemActionVM = ItemActionVM;
}

void UINV_ModalConfirmationWidget::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	MVVMView->SetViewModel("ItemActionViewModel", nullptr);
	CachedSelectionVM = nullptr;
	CachedItemActionVM = nullptr;
}