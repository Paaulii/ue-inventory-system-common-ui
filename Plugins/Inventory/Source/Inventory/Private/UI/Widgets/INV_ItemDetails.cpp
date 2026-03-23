// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemDetails.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"
#include "CommonTextBlock.h"
#include "Data/Types/INV_ItemActionType.h"
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
	Button_Drop->SetButtonVisibility(SelectedItem->GetDroppable());
	ToggleEquipButtonState(*SelectedItem);
}

void UINV_ItemDetails::ToggleEquipButtonState(const UINV_ItemViewModel& SelectedItem) const
{
	bool bShouldEquipButtonVisible = SelectedItem.GetEquippable() && !SelectedItem.GetIsEquipped();
	Button_Equip->SetButtonVisibility(bShouldEquipButtonVisible);

	bool bShouldUnEquipButtonVisible = SelectedItem.GetEquippable() && !bShouldEquipButtonVisible;
	Button_Unequip->SetButtonVisibility(bShouldUnEquipButtonVisible);
}

void UINV_ItemDetails::VM_OnEquipItemStateChange(const UINV_ItemViewModel* Item)
{
	UINV_ItemViewModel* SelectedItem = CachedSelectionVM->GetSelectedItem();

	if (!SelectedItem)
	{
		return;
	}

	
	if (Item == SelectedItem)
	{
		ToggleEquipButtonState(*SelectedItem);
	}
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

void UINV_ItemDetails::OnUnequipButtonSelected()
{
	DelegatePerformItemAction(FINV_ItemActionType::Unequip);
}

void UINV_ItemDetails::HandleItemActionPressed(const FINV_ItemActionType& ActionType) const
{
	if (CachedItemActionVM)
	{
		CachedItemActionVM->SetSelectedAction(ActionType);
		CachedItemActionVM->DelegateShowItemActionPopup();
		CachedItemActionVM->SetIsSingleItemQuantityAction(true);
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
		CachedItemActionVM->DelegatePerformAction(ActionType, SelectedItem->GetItemIdentification());
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
