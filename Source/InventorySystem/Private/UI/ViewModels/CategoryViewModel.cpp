// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/CategoryViewModel.h"

#include "Data/CategoryData.h"
#include "UI/ViewModels/ItemViewModel.h"

void UCategoryViewModel::Initialize(const FCategoryData& CategoryData)
{
	SetCategoryName(CategoryData.CategoryName);
	SetCategoryIcon(CategoryData.CategoryIcon);
	SetItemArray(CategoryData.Items);
}

void UCategoryViewModel::Deinitialize()
{
	//TODO: Deinitialize items
}

void UCategoryViewModel::SetCategoryName(const FText& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Name.ToString());
	UE_MVVM_SET_PROPERTY_VALUE(CategoryName, Name);
}

void UCategoryViewModel::SetCategoryIcon(UTexture2D* Icon)
{
	UE_MVVM_SET_PROPERTY_VALUE(CategoryIcon, Icon);
}

void UCategoryViewModel::SetItemArray(const TArray<TInstancedStruct<FItemData>>& ItemsData)
{
	CategoryItems.Empty();
	for (const TInstancedStruct<FItemData>& ItemData : ItemsData)
	{
		UItemViewModel* NewItemVM = NewObject<UItemViewModel>(this);
		NewItemVM->Initialize(ItemData.GetPtr(), this);
		CategoryItems.Add(NewItemVM);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CategoryItems);
}
