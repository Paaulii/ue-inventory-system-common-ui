// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemDetails.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"
#include "CommonTextBlock.h"
#include "Data/Types/INV_ItemActionType.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "UI/Widgets/INV_ItemActionButton.h"

void UINV_ItemDetails::VM_SelectedItemUpdated(UINV_ItemViewModel* SelectedItem)
{
	bool bIsItemEmpty = SelectedItem == nullptr;
	SetVisibility(bIsItemEmpty ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

	if (bIsItemEmpty)
	{
		return;
	}

	Text_Name->SetText(SelectedItem->GetItemName());
	Text_Description->SetText(SelectedItem->GetDescription());
	Text_Value->SetText(FText::AsNumber(SelectedItem->GetCurrencyValue()));
	Image_SelectedItem->SetBrushFromTexture(SelectedItem->GetLargeImage());

	Button_Consume->SetButtonVisibility(SelectedItem->GetConsumable());
	Button_Equip->SetButtonVisibility(SelectedItem->GetEquippable());
	Button_Drop->SetButtonVisibility(SelectedItem->GetDroppable());
}

void UINV_ItemDetails::OnConsumeButtonSelected()
{
	HandleItemActionPressed(FINV_ItemActionType::Consume);
}

void UINV_ItemDetails::OnDropButtonSelected()
{
	HandleItemActionPressed(FINV_ItemActionType::Drop);
}

void UINV_ItemDetails::OnEquipButtonSelected()
{
	DelegatePerformItemAction(FINV_ItemActionType::Equip);
}

void UINV_ItemDetails::HandleItemActionPressed(const FINV_ItemActionType& ActionType) const
{
	if (CachedItemActionVM)
	{
		CachedItemActionVM->SetSelectedAction(ActionType);
		CachedItemActionVM->DelegateShowItemActionPopup();
		CachedItemActionVM->SetIsSingleItemQuantityAction(false);
	}
}

void UINV_ItemDetails::DelegatePerformItemAction(const FINV_ItemActionType& ActionType) const
{
	if (!CachedItemActionVM || !CachedSelectionVM)
	{
		return;
	}

	if (UINV_ItemViewModel* SelectedItem = CachedSelectionVM->GetSelectedItem())
	{
		CachedItemActionVM->DelegatePerformAction(ActionType, SelectedItem->GetItemIdentification() );
	}
}


void UINV_ItemDetails::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_ItemActionViewModel* ItemActionVM = UIManager->GetViewModel<UINV_ItemActionViewModel>();
	MVVMView->SetViewModel("ItemActionViewModel", ItemActionVM);
	CachedItemActionVM = ItemActionVM;
}

void UINV_ItemDetails::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	MVVMView->SetViewModel("ItemActionViewModel", nullptr);
	CachedSelectionVM = nullptr;
	CachedItemActionVM = nullptr;
}

