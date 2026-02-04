// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/SelectionViewModel.h"

void USelectionViewModel::SetSelectedCategory(UCategoryViewModel* Category)
{
	UE_MVVM_SET_PROPERTY_VALUE(SelectedCategory, Category);
	TArray<TObjectPtr<UItemViewModel>> CategoryItems = SelectedCategory->GetCategoryItems();
	SetSelectedItem(CategoryItems.IsValidIndex(0) ? CategoryItems[0] : nullptr);
}

void USelectionViewModel::SetSelectedItem(UItemViewModel* ItemVM)
{
	UE_MVVM_SET_PROPERTY_VALUE(SelectedItem, ItemVM);
	
	if (ItemVM !=  nullptr)
	{
		UCategoryViewModel* SelectedItemCategory = SelectedItem->GetCategory();
		if ( SelectedItemCategory != SelectedCategory)
		{
			SetSelectedCategory(SelectedItemCategory);
		}
	}
}

void USelectionViewModel::TryRequestRefreshFocusTarget()
{
	if (RefreshFocusRequested == false)
	{
		UE_MVVM_SET_PROPERTY_VALUE(RefreshFocusRequested,true);
		UE_MVVM_SET_PROPERTY_VALUE(RefreshFocusRequested,false);
	}
}
