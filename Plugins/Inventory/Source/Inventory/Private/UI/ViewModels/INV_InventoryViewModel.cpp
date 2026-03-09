// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_InventoryViewModel.h"

#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "GameFramework/Character.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "UI/ViewModels/INV_ItemActionViewModel.h"

void UINV_InventoryViewModel::Initialize()
{
	Super::Initialize();
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		InventoryComponent = PlayerController->FindComponentByClass<UINV_InventoryComponent>();
		if (InventoryComponent)
		{
			InventoryComponent->OnInventoryDataChanged.BindUObject(this, &UINV_InventoryViewModel::RebuildInventory);
		}
	}
}

void UINV_InventoryViewModel::Deinitialize()
{
	Super::Deinitialize();
	if (!InventoryComponent)
	{
		return;
	}

	InventoryComponent->OnInventoryDataChanged.Unbind();
}

void UINV_InventoryViewModel::RebuildInventory(const FINV_InventoryDisplayData& InventoryData)
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
	
	Categories.Empty();
}

void UINV_InventoryViewModel::InitializeCategoryVM(const TArray<FINV_CategoryDisplayData>& CategoryDataArray)
{
	ResetCategories();
	
	for (const FINV_CategoryDisplayData& CategoryData : CategoryDataArray)
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
