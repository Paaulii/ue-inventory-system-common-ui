// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_SelectionViewModel.h"

void UINV_SelectionViewModel::SetSelectedCategory(UINV_CategoryViewModel* Category)
{
	UE_MVVM_SET_PROPERTY_VALUE(SelectedCategory, Category);

	if (Category == nullptr)
	{
		SetSelectedItem(nullptr);
		return;
	}
	
	TArray<TObjectPtr<UINV_ItemViewModel>> CategoryItems = SelectedCategory->GetCategoryItems();
	SetSelectedItem(CategoryItems.IsValidIndex(0) ? CategoryItems[0] : nullptr);
}

void UINV_SelectionViewModel::SetSelectedItem(UINV_ItemViewModel* ItemVM)
{
	UE_MVVM_SET_PROPERTY_VALUE(SelectedItem, ItemVM);

	if (ItemVM !=  nullptr)
	{
		UINV_CategoryViewModel* SelectedItemCategory = SelectedItem->GetCategory();
		if ( SelectedItemCategory != SelectedCategory)
		{
			SetSelectedCategory(SelectedItemCategory);
		}
	}
}

void UINV_SelectionViewModel::TryRequestRefreshFocusTarget()
{
	if (RefreshFocusRequested == false)
	{
		UE_MVVM_SET_PROPERTY_VALUE(RefreshFocusRequested,true);
		UE_MVVM_SET_PROPERTY_VALUE(RefreshFocusRequested,false);
	}
}
