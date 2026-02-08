// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_CategoryViewModel.h"

#include "Data/INV_CategoryData.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_CategoryViewModel::Initialize(const FINV_CategoryData& CategoryData)
{
	SetCategoryName(CategoryData.CategoryName);
	SetCategoryIcon(CategoryData.CategoryIcon);
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

void UINV_CategoryViewModel::SetCategoryIcon(UTexture2D* Icon)
{
	UE_MVVM_SET_PROPERTY_VALUE(CategoryIcon, Icon);
}

void UINV_CategoryViewModel::SetItemArray(const TArray<TInstancedStruct<FINV_ItemData>>& ItemsData)
{
	CategoryItems.Empty();
	for (const TInstancedStruct<FINV_ItemData>& ItemData : ItemsData)
	{
		UINV_ItemViewModel* NewItemVM = NewObject<UINV_ItemViewModel>(this);
		NewItemVM->Initialize(ItemData.GetPtr(), this);
		CategoryItems.Add(NewItemVM);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CategoryItems);
}
