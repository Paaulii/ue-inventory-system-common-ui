// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/CategoryViewModel.h"

#include "Data/CategoryData.h"

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

void UCategoryViewModel::SetItemArray(const TArray<TInstancedStruct<FItemData>>& ItemData)
{
	// TODO: Create VM for each Item Data
}
