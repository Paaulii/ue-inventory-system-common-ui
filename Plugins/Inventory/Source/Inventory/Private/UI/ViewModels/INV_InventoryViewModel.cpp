// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "UI/ViewModels/INV_EquipmentViewModel.h"

void UINV_InventoryViewModel::Initialize()
{
	Super::Initialize();
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		InventoryComponent = PlayerController->FindComponentByClass<UINV_InventoryComponent>();
		if (InventoryComponent)
		{
			InventoryComponent->OnInventoryDataParsed.BindUObject(this, &UINV_InventoryViewModel::RebuildInventory);
			InventoryComponent->OnCategoryItemsChanged.BindUObject(this, &UINV_InventoryViewModel::UpdateCategoryData);
			InventoryComponent->OnItemEquipped.BindUObject(this, &UINV_InventoryViewModel::HandleItemEquipped);
			InventoryComponent->OnItemUnequipped.BindUObject(this, &UINV_InventoryViewModel::HandleItemUnequipped);
		}
	}

	SetEquipment(NewObject<UINV_EquipmentViewModel>(this));
}

void UINV_InventoryViewModel::Deinitialize()
{
	Super::Deinitialize();
	if (!InventoryComponent)
	{
		return;
	}

	InventoryComponent->OnInventoryDataParsed.Unbind();
	InventoryComponent->OnCategoryItemsChanged.Unbind();
	InventoryComponent->OnItemEquipped.Unbind();
	InventoryComponent->OnItemUnequipped.Unbind();
}

void UINV_InventoryViewModel::RebuildInventory(const FINV_InventoryDisplayData& InventoryData)
{
	SetCurrencyAmount(InventoryData.CurrencyAmount);
	SetMaxItemsCapacity(InventoryData.MaxItemsCapacity);
	InitializeCategoryVM(InventoryData.Categories);
}

void UINV_InventoryViewModel::UpdateCategoryData(const FINV_CategoryDisplayData& CategoryData)
{
	for (UINV_CategoryViewModel* CategoryVM : Categories)
	{
		if (CategoryVM->GetCategoryTag() == CategoryData.Tag)
		{
			CategoryVM->SetItems(CategoryData.Items);
			break;
		}
	}
}

void UINV_InventoryViewModel::HandleItemEquipped(const FINV_ItemIdentification& ItemIdentification)
{
	if (UINV_ItemViewModel* FoundItem = GetItemById(ItemIdentification))
	{
		Equipment->OnEquipItem(*FoundItem);
	}
}

void UINV_InventoryViewModel::HandleItemUnequipped(const FINV_ItemIdentification& ItemIdentification)
{
	if (UINV_ItemViewModel* FoundItem = GetItemById(ItemIdentification))
	{
		Equipment->OnUnequipItem(*FoundItem);
	}
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

void UINV_InventoryViewModel::SetEquipment(UINV_EquipmentViewModel* EquipmentVM)
{
	UE_MVVM_SET_PROPERTY_VALUE(Equipment, EquipmentVM);
}


UINV_ItemViewModel* UINV_InventoryViewModel::GetItemById(const FINV_ItemIdentification& ItemIdentification)
{
	for (const auto& Cat : Categories)
	{
		for (UINV_ItemViewModel* ItemVM :Cat->GetCategoryItems())
		{
			if (ItemVM->GetItemIdentification().Id == ItemIdentification.Id)
			{
				return ItemVM;
			}
		}
	}

	return nullptr;
}