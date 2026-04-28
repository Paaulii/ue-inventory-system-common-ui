#include "UI/Widgets/INV_ItemDetails.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Data/Types/INV_ItemActionType.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/Widgets/INV_ItemActionButton.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_ItemDetails::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager.GetViewModel<UINV_SelectionViewModel>();
	checkf(SelectionVM, TEXT("UIManager cannot find SelectionViewMode. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
	CachedSelectionVM = SelectionVM;
	
	UINV_ItemActionViewModel* ItemActionVM = UIManager.GetViewModel<UINV_ItemActionViewModel>();
	checkf(ItemActionVM, TEXT("UIManager cannot find ItemActionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("ItemActionViewModel"), ItemActionVM);
	CachedItemActionVM = ItemActionVM;
}

void UINV_ItemDetails::ClearViewModelsCache()
{
	MVVMView->SetViewModel(FName("SelectionViewModel"), nullptr);
	MVVMView->SetViewModel(FName("ItemActionViewModel"), nullptr);
	CachedSelectionVM = nullptr;
	CachedItemActionVM = nullptr;
}

void UINV_ItemDetails::VM_SelectedItemUpdated(const UINV_ItemViewModel* SelectedItem)
{
	bool bIsItemEmpty = SelectedItem == nullptr;
	SetVisibility(bIsItemEmpty ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

	if (bIsItemEmpty)
	{
		return;
	}

	NameText->SetText(SelectedItem->GetItemName());
	DescriptionText->SetText(SelectedItem->GetDescription());
	ValueText->SetText(FText::AsNumber(SelectedItem->GetCurrencyValue()));
	SelectedItemImage->SetBrushFromTexture(SelectedItem->GetLargeImage());
	ConsumeButton->SetButtonVisibility(SelectedItem->GetbIsConsumable());
	DropButton->SetButtonVisibility(SelectedItem->GetbIsDroppable());
	ToggleEquipButtonState(*SelectedItem);
}

void UINV_ItemDetails::DelegateShowItemActionPopup(const FINV_ItemActionType& ActionType) const
{
	if (CachedItemActionVM && CachedSelectionVM->GetSelectedItem())
	{
		CachedItemActionVM->SetSelectedAction(ActionType);
		CachedItemActionVM->DelegateShowItemActionPopup();
	}
}

void UINV_ItemDetails::DelegatePerformItemAction(const FINV_ItemActionType& ActionType) const
{
	if (!CachedItemActionVM || !CachedSelectionVM)
	{
		return;
	}

	if (const UINV_ItemViewModel* SelectedItem = CachedSelectionVM->GetSelectedItem())
	{
		CachedItemActionVM->DelegatePerformAction(ActionType, *SelectedItem);
	}
}

void UINV_ItemDetails::VM_OnEquipItemStateChange(const UINV_ItemViewModel* Item)
{
	if (!CachedSelectionVM)
	{
		return;
	}
	
	const UINV_ItemViewModel* SelectedItem = CachedSelectionVM->GetSelectedItem();

	if (!SelectedItem)
	{
		return;
	}

	
	if (Item == SelectedItem)
	{
		ToggleEquipButtonState(*SelectedItem);
	}
}

void UINV_ItemDetails::ToggleEquipButtonState(const UINV_ItemViewModel& SelectedItem) const
{
	bool bShouldEquipButtonVisible = SelectedItem.GetbIsEquippable() && !SelectedItem.GetbIsEquipped();
	EquipButton->SetButtonVisibility(bShouldEquipButtonVisible);

	bool bShouldUnEquipButtonVisible = SelectedItem.GetbIsEquippable() && !bShouldEquipButtonVisible;
	UnequipButton->SetButtonVisibility(bShouldUnEquipButtonVisible);
}

void UINV_ItemDetails::OnConsumeButtonSelected()
{
	DelegateShowItemActionPopup(FINV_ItemActionType::Consume);
}

void UINV_ItemDetails::OnDropButtonSelected()
{
	DelegateShowItemActionPopup(FINV_ItemActionType::Drop);
}

void UINV_ItemDetails::OnEquipButtonSelected()
{
	DelegatePerformItemAction(FINV_ItemActionType::Equip);
}

void UINV_ItemDetails::OnUnequipButtonSelected()
{
	DelegatePerformItemAction(FINV_ItemActionType::Unequip);
}

void UINV_ItemDetails::OnSellButtonSelected()
{
	DelegateShowItemActionPopup(FINV_ItemActionType::Sell);
}