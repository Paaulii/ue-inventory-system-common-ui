#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_CategoryViewModel::Initialize(const FINV_CategoryDisplayData& CategoryData)
{
	UE_MVVM_SET_PROPERTY_VALUE(CategoryName, CategoryData.CategoryName);
	SetItems(CategoryData.Items);
	Tag = CategoryData.Tag;
}

void UINV_CategoryViewModel::SetItems(const TArray<FINV_ItemDisplayData>& ItemsData)
{
	CategoryItems.Empty();
	for (const auto& ItemData : ItemsData)
	{
		UINV_ItemViewModel* NewItemVM = NewObject<UINV_ItemViewModel>(this);
		NewItemVM->Initialize(ItemData, this);
		CategoryItems.Add(NewItemVM);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CategoryItems);
}
