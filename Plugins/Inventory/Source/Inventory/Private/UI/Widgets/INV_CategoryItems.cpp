// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_CategoryItems.h"

#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "View/MVVMView.h"
#include "Components/DynamicEntryBox.h"
#include "UI/Widgets/INV_InputAction.h"
#include "UI/Widgets/INV_ItemTile.h"

void UINV_CategoryItems::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PopulateSlots();
}

void UINV_CategoryItems::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_InventoryViewModel* InventoryVM = UIManager->GetViewModel<UINV_InventoryViewModel>();
	CachedInventoryVM = InventoryVM;
	MVVMView->SetViewModel("InventoryViewModel", InventoryVM);
	
	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	CachedSelectionVM = SelectionVM;
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
}

void UINV_CategoryItems::ClearViewModelsCache()
{
	CachedSelectionVM = nullptr;
	CachedCategoryVM = nullptr;
	CachedInventoryVM = nullptr;
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	MVVMView->SetViewModel("InventoryViewModel", nullptr);
	MVVMView->SetViewModel("CategoryViewModel", nullptr);
}

void UINV_CategoryItems::VM_ForceFocusEvaluation(bool bHasPendingRequest)
{
	if (!bHasPendingRequest)
	{
		return;
	}

	RequestRefreshFocus();
}

FText UINV_CategoryItems::VM_GetItemsCapacityText(UINV_ItemViewModel* ItemVM) const
{
	if (CachedInventoryVM == nullptr)
	{
		return FText::GetEmpty();
	}

	int ItemIndex = GetItemIndexForSelectedCategory();
	int ItemsCount = CachedItemsVM.Num();

	FText ItemCapacityText = FText::Format(
		FText::FromString(TEXT("{0}/{1}")),
		ItemIndex + 1,
		ItemsCount
	);
	return ItemCapacityText;
}

UUserWidget* UINV_CategoryItems::GetFocusTile() const
{
	int SelectedItemIndex = FMath::Max(GetItemIndexForSelectedCategory(), 0);
	int MinItemIndex = CurrentPage * MaxDynamicEntryBoxCapacity;
	int MaxItemIndex = MinItemIndex + MaxDynamicEntryBoxCapacity - 1;

	if (SelectedItemIndex < MinItemIndex || SelectedItemIndex > MaxItemIndex)
	{
		SelectedItemIndex = 0;
	}

	SelectedItemIndex = SelectedItemIndex % MaxDynamicEntryBoxCapacity;

	TArray<UUserWidget*> CategoryItems = DynamicEntryBox_Items->GetAllEntries();

	if (CategoryItems.IsValidIndex(SelectedItemIndex))
	{
		return CategoryItems[SelectedItemIndex];
	}

	return nullptr;
}


void UINV_CategoryItems::ChangePage(int PageOffset)
{
	int PageNumber = CurrentPage + PageOffset;

	if (PageNumber >= 0 && PageNumber <= PageCount)
	{
		CurrentPage = PageNumber;
		VM_CategoryItemsChanged(CachedItemsVM);

		// Item needs to be re-selected manually, because if player selects first item and changes page the ItemTile is still the same,
		// it's still focused, so it won't invoke selecting item by itself,
		// which means first item on the new page won't be selected
		SelectFirstItemOnPage();
	}
}

void UINV_CategoryItems::SelectFirstItemOnPage()
{
	int FirstItemOnPageIndex = CurrentPage * MaxDynamicEntryBoxCapacity;
	if (CachedItemsVM.IsValidIndex(FirstItemOnPageIndex))
	{
		CachedSelectionVM->SetSelectedItem(CachedItemsVM[FirstItemOnPageIndex]);
	}
}

void UINV_CategoryItems::TryFocusOnFirstTile(UINV_ItemTile* ItemTile)
{
	ItemTile->OnItemSelected.RemoveDynamic(this, &UINV_CategoryItems::TryFocusOnFirstTile);
	RequestRefreshFocus();
}

void UINV_CategoryItems::UpdateSlots(TArray<UINV_ItemViewModel*> ItemViewModels)
{
	int IndexOffset = FMath::Max(CurrentPage * MaxDynamicEntryBoxCapacity, 0);
	for (int i = 0; i < MaxDynamicEntryBoxCapacity; i++)
	{
		int CurrentIndex = i + IndexOffset;

		UINV_ItemViewModel* ItemVM = CurrentIndex < ItemViewModels.Num() ? ItemViewModels[CurrentIndex] : nullptr;
		ItemTiles[i]->SetViewModels(ItemVM, ItemVM != nullptr ? CachedSelectionVM : nullptr);
	}

	RequestRefreshFocus();
}

void UINV_CategoryItems::PopulateSlots()
{
	ItemTiles.Empty();
	for (int i = 0; i < MaxDynamicEntryBoxCapacity; i++)
	{
		UINV_ItemTile* ItemTile = CreateSlot();

		if (i == 0)
		{
			ItemTile->OnItemSelected.AddDynamic(this, &UINV_CategoryItems::TryFocusOnFirstTile);
		}
	}
}

void UINV_CategoryItems::UpdatePageButtonVisibility()
{
	InputAction_NextPage->SetVisibility(CurrentPage < PageCount && PageCount > 0
		                                    ? ESlateVisibility::Visible
		                                    : ESlateVisibility::Hidden);
	InputAction_PreviousPage->SetVisibility(CurrentPage == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UINV_CategoryItems::VM_CategoryItemsChanged(TArray<UINV_ItemViewModel*> ItemViewModels)
{
	PageCount = FMath::FloorToInt(static_cast<float>(ItemViewModels.Num() / MaxDynamicEntryBoxCapacity));
	UpdatePageButtonVisibility();
	UpdateSlots(ItemViewModels);
}

void UINV_CategoryItems::VM_SelectedCategoryChanged(UINV_CategoryViewModel* CategoryVM)
{
	CurrentPage = 0;
	CachedCategoryVM = CategoryVM;
	if (CategoryVM)
	{
		CachedItemsVM = CategoryVM->GetCategoryItems();
	}
	MVVMView->SetViewModel("CategoryViewModel", CategoryVM);
}

UINV_ItemTile* UINV_CategoryItems::CreateSlot()
{
	UINV_ItemTile* ItemTile = Cast<UINV_ItemTile>(DynamicEntryBox_Items->CreateEntry());
	ItemTiles.Add(ItemTile);
	return ItemTile;
}

int UINV_CategoryItems::GetItemIndexForSelectedCategory() const
{
	if (CachedSelectionVM == nullptr || CachedItemsVM.IsEmpty())
	{
		return -1;
	}

	UINV_ItemViewModel* SelectedItem = CachedSelectionVM->GetSelectedItem();

	if (!SelectedItem)
	{
		return -1;
	}
	
	for (int i = 0; i < CachedItemsVM.Num(); i++)
	{
		if (CachedItemsVM[i]->GetItemIdentification().UID == SelectedItem->GetItemIdentification().UID)
		{
			return i;
		}
	}
	
	return -1;
}
