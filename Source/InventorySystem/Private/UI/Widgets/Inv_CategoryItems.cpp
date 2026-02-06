// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/Inv_CategoryItems.h"

#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/ViewModels/CategoryViewModel.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "View/MVVMView.h"
#include "Components/DynamicEntryBox.h"
#include "UI/Widgets/Inv_InputAction.h"
#include "UI/Widgets/ItemTile.h"

void UInv_CategoryItems::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PopulateSlots();
}

void UInv_CategoryItems::CacheViewModels(UUIManagerSubsystem* UIManager)
{
	MVVMView->SetViewModel("SelectionViewModel", UIManager->GetSelectionVM());
	CachedSelectionVM = UIManager->GetSelectionVM();

	MVVMView->SetViewModel("InventoryViewModel", UIManager->GetInventoryVM());
	CachedInventoryVM = UIManager->GetInventoryVM();
}

void UInv_CategoryItems::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	MVVMView->SetViewModel("InventoryViewModel", nullptr);
	MVVMView->SetViewModel("CategoryViewModel", nullptr);
	CachedSelectionVM = nullptr;
	CachedCategoryVM = nullptr;
	CachedInventoryVM = nullptr;
}

void UInv_CategoryItems::VM_ForceFocusEvaluation(bool bHasPendingRequest)
{
	if (!bHasPendingRequest)
	{
		return;
	}

	RequestRefreshFocus();
}

FText UInv_CategoryItems::VM_GetItemsCapacityText(UItemViewModel* ItemVM) const
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

UUserWidget* UInv_CategoryItems::GetFocusTile() const
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


void UInv_CategoryItems::ChangePage(int PageOffset)
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

void UInv_CategoryItems::SelectFirstItemOnPage()
{
	int FirstItemOnPageIndex = CurrentPage * MaxDynamicEntryBoxCapacity;
	if (CachedItemsVM.IsValidIndex(FirstItemOnPageIndex))
	{
		CachedSelectionVM->SetSelectedItem(CachedItemsVM[FirstItemOnPageIndex]);
	}
}

void UInv_CategoryItems::OnItemTileReady(UItemTile* ItemTile)
{
	ItemTile->OnItemSelected.RemoveDynamic(this, &UInv_CategoryItems::OnItemTileReady);
	RequestRefreshFocus();
}

void UInv_CategoryItems::UpdateSlots(TArray<UItemViewModel*> ItemViewModels)
{
	int IndexOffset = FMath::Max(CurrentPage * MaxDynamicEntryBoxCapacity, 0);
	for (int i = 0; i < MaxDynamicEntryBoxCapacity; i++)
	{
		int CurrentIndex = i + IndexOffset;

		UItemViewModel* ItemVM = CurrentIndex < ItemViewModels.Num() ? ItemViewModels[CurrentIndex] : nullptr;
		ItemTiles[i]->SetViewModels(ItemVM, ItemVM != nullptr ? CachedSelectionVM : nullptr);
	}

	RequestRefreshFocus();
}

void UInv_CategoryItems::PopulateSlots()
{
	ItemTiles.Empty();
	for (int i = 0; i < MaxDynamicEntryBoxCapacity; i++)
	{
		UItemTile* ItemTile = CreateSlot();

		if (i == 0)
		{
			ItemTile->OnItemSelected.AddDynamic(this, &UInv_CategoryItems::OnItemTileReady);
		}
	}
}

void UInv_CategoryItems::UpdatePageButtonVisibility()
{
	InputAction_NextPage->SetVisibility(CurrentPage < PageCount && PageCount > 0
		                                    ? ESlateVisibility::Visible
		                                    : ESlateVisibility::Hidden);
	InputAction_PreviousPage->SetVisibility(CurrentPage == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UInv_CategoryItems::VM_CategoryItemsChanged(TArray<UItemViewModel*> ItemViewModels)
{
	PageCount = FMath::FloorToInt(static_cast<float>(ItemViewModels.Num() / MaxDynamicEntryBoxCapacity));
	UpdatePageButtonVisibility();
	UpdateSlots(ItemViewModels);
}

void UInv_CategoryItems::VM_SelectedCategoryChanged(UCategoryViewModel* CategoryVM)
{
	CurrentPage = 0;
	CachedCategoryVM = CategoryVM;
	if (CategoryVM)
	{
		CachedItemsVM = CategoryVM->GetCategoryItems();
	}
	MVVMView->SetViewModel("CategoryViewModel", CategoryVM);
}

UItemTile* UInv_CategoryItems::CreateSlot()
{
	UItemTile* ItemTile = Cast<UItemTile>(DynamicEntryBox_Items->CreateEntry());
	ItemTiles.Add(ItemTile);
	return ItemTile;
}

int UInv_CategoryItems::GetItemIndexForSelectedCategory() const
{
	if (CachedSelectionVM == nullptr || CachedItemsVM.IsEmpty())
	{
		return -1;
	}

	int ItemIndex = CachedItemsVM.Find(CachedSelectionVM->GetSelectedItem());
	return ItemIndex;
}
