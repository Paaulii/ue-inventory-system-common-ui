// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_CategoryViewModel::Initialize(const FINV_CategoryDisplayData& CategoryData)
{
	SetCategoryName(CategoryData.CategoryName);
	SetItemArray(CategoryData.Items);
}

void UINV_CategoryViewModel::Deinitialize()
{
	//TODO: Deinitialize items
}

void UINV_CategoryViewModel::SetCategoryName(const FText& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Name.ToString());
	UE_MVVM_SET_PROPERTY_VALUE(CategoryName, Name);
}

void UINV_CategoryViewModel::SetItemArray(const TArray<FINV_ItemDisplayData>& ItemsData)
{
	CategoryItems.Empty();
	for (const FINV_ItemDisplayData& ItemData : ItemsData)
	{
		UINV_ItemViewModel* NewItemVM = NewObject<UINV_ItemViewModel>(this);
		NewItemVM->Initialize(ItemData, this);
		CategoryItems.Add(NewItemVM);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CategoryItems);
}
