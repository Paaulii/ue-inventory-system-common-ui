// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/SelectionViewModel.h"

void USelectionViewModel::SetSelectedCategory(UCategoryViewModel* Category)
{
	UE_MVVM_SET_PROPERTY_VALUE(SelectedCategory, Category);
}
