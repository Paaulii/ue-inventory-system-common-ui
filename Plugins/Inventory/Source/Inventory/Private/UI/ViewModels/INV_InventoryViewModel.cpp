// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_InventoryViewModel.h"

#include "Data/INV_InventoryData.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"

void UINV_InventoryViewModel::Initialize()
{
	// TODO: Add logic to subscribe to player's inventory data events
}

void UINV_InventoryViewModel::Deinitialize()
{
	// TODO: Unsubscribe from player's events
}

void UINV_InventoryViewModel::RebuildInventory(const FINV_InventoryData& InventoryData)
{
	SetCurrencyAmount(InventoryData.CurrencyAmount);
	SetMaxItemsCapacity(InventoryData.MaxItemsCapacity);
	InitializeCategoryVM(InventoryData.Categories);
}

void UINV_InventoryViewModel::ResetCategories()
{
	for (UINV_CategoryViewModel*CategoryViewModel : Categories)
	{
		CategoryViewModel->Deinitialize();
	}
}

void UINV_InventoryViewModel::InitializeCategoryVM(const TArray<FINV_CategoryData>& CategoryDataArray)
{
	ResetCategories();
	
	for (const FINV_CategoryData& CategoryData : CategoryDataArray)
	{
		UINV_CategoryViewModel* CategoryVM = NewObject<UINV_CategoryViewModel>(this);
		CategoryVM->Initialize(CategoryData);
		Categories.Add(CategoryVM);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Categories);
}

void UINV_InventoryViewModel::SetCurrencyAmount(float Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(CurrencyAmount, Value);
}

void UINV_InventoryViewModel::SetMaxItemsCapacity(int Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxItemsCapacity, Value);
}
