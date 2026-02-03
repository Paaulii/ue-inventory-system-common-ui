// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/Inv_CategoryItems.h"

#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/ViewModels/CategoryViewModel.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "View/MVVMView.h"
#include "Components/DynamicEntryBox.h"
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

	CachedCategoryVM = Cast<UCategoryViewModel>(MVVMView->GetViewModel("CategoryViewModel").GetObject());
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

FText UInv_CategoryItems::VM_GetItemsCapacityText(TArray<UItemViewModel*> ItemsVM) const
{
	if (CachedInventoryVM == nullptr)
	{
		return FText::GetEmpty();
	}

	FText ItemCapacityText = FText::Format(
		FText::FromString(TEXT("{0}/{1}")),
		ItemsVM.Num(),
		CachedInventoryVM->GetMaxItemsCapacity()
	);
	return ItemCapacityText;
}

UUserWidget* UInv_CategoryItems::GetFocusTile() const
{
	int SelectedItemIndex = FMath::Max(GetItemIndexForSelectedCategory(), 0);
	TArray<UUserWidget*> CategoryItems = DynamicEntryBox_Items->GetAllEntries();

	if (CategoryItems.Num() > 0)
	{
		return CategoryItems[SelectedItemIndex];
	}

	return nullptr;
}

void UInv_CategoryItems::OnItemTileReady(UItemTile* ItemTile)
{
	ItemTile->OnItemSelected.RemoveDynamic(this, &UInv_CategoryItems::OnItemTileReady);
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

void UInv_CategoryItems::VM_UpdateSlots(TArray<UItemViewModel*> ItemsVM)
{
	for (int i = 0; i < ItemTiles.Num(); i++)
	{
		UItemViewModel* ItemVM = i < ItemsVM.Num() ? ItemsVM[i] : nullptr;
		ItemTiles[i]->SetViewModels(ItemVM, ItemVM != nullptr ? CachedSelectionVM : nullptr);
		
	}
	
	RequestRefreshFocus();
}

UItemTile* UInv_CategoryItems::CreateSlot()
{
	UItemTile* ItemTile = Cast<UItemTile>(DynamicEntryBox_Items->CreateEntry());
	ItemTiles.Add(ItemTile);
	return ItemTile;
}

int UInv_CategoryItems::GetItemIndexForSelectedCategory() const
{
	if (CachedSelectionVM == nullptr || CachedCategoryVM == nullptr)
	{
		return -1;
	}

	int ItemIndex = CachedCategoryVM->GetCategoryItems().Find(CachedSelectionVM->GetSelectedItem());
	return ItemIndex;
}
