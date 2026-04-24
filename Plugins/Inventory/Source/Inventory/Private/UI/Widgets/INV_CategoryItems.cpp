#include "UI/Widgets/INV_CategoryItems.h"
#include "Components/DynamicEntryBox.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/Widgets/INV_InputAction.h"
#include "UI/Widgets/INV_ItemTile.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_CategoryItems::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PopulateSlots();
}

void UINV_CategoryItems::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_InventoryViewModel* InventoryVM = UIManager.GetViewModel<UINV_InventoryViewModel>();
	checkf(InventoryVM, TEXT("UIManager cannot find InventoryViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	CachedInventoryVM = InventoryVM;
	MVVMView->SetViewModel(FName("InventoryViewModel"), InventoryVM);

	UINV_SelectionViewModel* SelectionVM = UIManager.GetViewModel<UINV_SelectionViewModel>();
	checkf(SelectionVM, TEXT("UIManager cannot find SelectionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	CachedSelectionVM = SelectionVM;
	MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
}

void UINV_CategoryItems::ClearViewModelsCache()
{
	CachedSelectionVM = nullptr;
	CachedCategoryVM = nullptr;
	CachedInventoryVM = nullptr;
	MVVMView->SetViewModel(FName("SelectionViewModel"), nullptr);
	MVVMView->SetViewModel(FName("InventoryViewModel"), nullptr);
	MVVMView->SetViewModel(FName("CategoryViewModel"), nullptr);
}

void UINV_CategoryItems::PopulateSlots()
{
	ItemTiles.Empty();
	for (int i = 0; i < MaxDynamicEntryBoxCapacity; i++)
	{
		CreateSlot();
	}
}

UINV_ItemTile* UINV_CategoryItems::CreateSlot()
{
	UINV_ItemTile* ItemTile = Cast<UINV_ItemTile>(DynamicEntryBoxItems->CreateEntry());
	ItemTiles.Add(ItemTile);
	return ItemTile;
}

void UINV_CategoryItems::VM_CategoryItemsChanged(const TArray<UINV_ItemViewModel*>& ItemViewModels)
{
	CachedItemsVM = ItemViewModels;
	PageCount = static_cast<float>(ItemViewModels.Num() / MaxDynamicEntryBoxCapacity);
	UpdatePageButtonVisibility();
	UpdateSlots(ItemViewModels);
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

	if (CachedSelectionVM && CachedSelectionVM->GetSelectedItem())
	{
		UINV_ItemViewModel** ItemVM = ItemViewModels.FindByPredicate([this](const UINV_ItemViewModel* ItemVM)
		{
			return ItemVM->GetItemIdentification().Id == CachedSelectionVM->GetSelectedItem()->GetItemIdentification().Id;
		});

		if (!ItemVM)
		{
			SelectFirstItemOnPage();
		}
	}

	RequestRefreshFocus();
}

void UINV_CategoryItems::UpdatePageButtonVisibility()
{
	NextPageInputAction->SetVisibility(CurrentPage < PageCount && PageCount > 0
											? ESlateVisibility::Visible
											: ESlateVisibility::Hidden);
	PreviousPageInputAction->SetVisibility(CurrentPage == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UINV_CategoryItems::ChangePage(int32 PageOffset)
{
	int PageNumber = CurrentPage + PageOffset;

	if (PageNumber >= 0 && PageNumber <= PageCount)
	{
		CurrentPage = PageNumber;
		VM_CategoryItemsChanged(CachedItemsVM);

		// Item needs to be re-selected manually, because if player selects first item and changes page the ItemTile is still the same,
		// it's still focused, so it won't invoke selecting item by itself,
		// which means first item on the new page won't be selected (won't be highlighted)
		SelectFirstItemOnPage();
	}
}

void UINV_CategoryItems::SelectFirstItemOnPage()
{
	int FirstItemOnPageIndex = CurrentPage * MaxDynamicEntryBoxCapacity;
	UINV_ItemViewModel* SelectedItem = FirstItemOnPageIndex < CachedItemsVM.Num()
										   ? CachedItemsVM[FirstItemOnPageIndex]
										   : nullptr;
	CachedSelectionVM->SetSelectedItem(SelectedItem);
}

void UINV_CategoryItems::VM_ForceFocusEvaluation(bool bHasPendingRequest)
{
	if (!bHasPendingRequest)
	{
		return;
	}

	RequestRefreshFocus();
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

	TArray<UUserWidget*> CategoryItems = DynamicEntryBoxItems->GetAllEntries();

	if (CategoryItems.IsValidIndex(SelectedItemIndex))
	{
		return CategoryItems[SelectedItemIndex];
	}

	return nullptr;
}

void UINV_CategoryItems::VM_SelectedCategoryChanged(UINV_CategoryViewModel* CategoryVM)
{
	CurrentPage = 0;
	CachedCategoryVM = CategoryVM;
	MVVMView->SetViewModel(FName("CategoryViewModel"), CategoryVM);
}

FText UINV_CategoryItems::VM_GetItemsCapacityText(const UINV_ItemViewModel* ItemVM) const
{
	int ItemIndex = GetItemIndexForSelectedCategory();
	int ItemsCount = CachedItemsVM.Num();

	FText ItemCapacityText = FText::Format(
		FText::FromString(TEXT("{0}/{1}")),
		ItemIndex + 1,
		ItemsCount
	);
	return ItemCapacityText;
}

int UINV_CategoryItems::GetItemIndexForSelectedCategory() const
{
	if (CachedSelectionVM == nullptr || CachedItemsVM.IsEmpty())
	{
		return INDEX_NONE;
	}

	const UINV_ItemViewModel* SelectedItem = CachedSelectionVM->GetSelectedItem();

	if (!SelectedItem)
	{
		return INDEX_NONE;
	}

	for (int i = 0; i < CachedItemsVM.Num(); i++)
	{
		if (CachedItemsVM[i]->GetItemIdentification().Id == SelectedItem->GetItemIdentification().Id)
		{
			return i;
		}
	}

	return INDEX_NONE;
}
