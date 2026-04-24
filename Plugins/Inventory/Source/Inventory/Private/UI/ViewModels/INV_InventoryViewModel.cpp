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
		checkf(InventoryComponent, TEXT("PlayerController doesn't contain InventoryComponent! Make sure to add that component otherwise Inventory System won't work."));
		InventoryComponent->OnInventoryDataParsed.BindUObject(this, &UINV_InventoryViewModel::RebuildInventory);
		InventoryComponent->OnCategoryItemsChanged.BindUObject(this, &UINV_InventoryViewModel::UpdateCategoryData);
		InventoryComponent->OnCurrencyChanged.BindUObject(this, &UINV_InventoryViewModel::HandleCurrencyChanged);
		InventoryComponent->OnItemEquipped.AddDynamic(this, &UINV_InventoryViewModel::HandleItemEquipped);
		InventoryComponent->OnItemUnequipped.AddDynamic(this, &UINV_InventoryViewModel::HandleItemUnequipped);
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
	InventoryComponent->OnCurrencyChanged.Unbind();
	InventoryComponent->OnItemEquipped.RemoveDynamic(this, &UINV_InventoryViewModel::HandleItemEquipped);
	InventoryComponent->OnItemUnequipped.RemoveDynamic(this, &UINV_InventoryViewModel::HandleItemUnequipped);
}

void UINV_InventoryViewModel::RebuildInventory(const FINV_InventoryDisplayData& InventoryData)
{
	SetCurrencyAmount(InventoryData.CurrencyAmount);
	SetMaxItemsCapacity(InventoryData.MaxItemsCapacity);
	InitializeCategoryVM(InventoryData.Categories);
}

void UINV_InventoryViewModel::InitializeCategoryVM(const TArray<FINV_CategoryDisplayData>& CategoryDataArray)
{
	Categories.Empty();
	
	for (const auto& CategoryData : CategoryDataArray)
	{
		UINV_CategoryViewModel* CategoryVM = NewObject<UINV_CategoryViewModel>(this);
		CategoryVM->Initialize(CategoryData);
		Categories.Add(CategoryVM);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Categories);
}

void UINV_InventoryViewModel::UpdateCategoryData(const FINV_CategoryDisplayData& CategoryData)
{
	for (const auto& CategoryVM : Categories)
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
	UINV_ItemViewModel* FoundItem = GetItemById(ItemIdentification);
	if (ensureMsgf(FoundItem, TEXT("Couldn't equip item. Item ViewModel not found.")))
	{
		Equipment->OnEquipItem(*FoundItem);
	}
}

void UINV_InventoryViewModel::HandleItemUnequipped(const FINV_ItemIdentification& ItemIdentification)
{
	UINV_ItemViewModel* FoundItem = GetItemById(ItemIdentification);
	if (ensureMsgf(FoundItem, TEXT("Couldn't unequip item. Item ViewModel not found.")))
	{
		Equipment->OnUnequipItem(*FoundItem);
	}
}

void UINV_InventoryViewModel::HandleCurrencyChanged(const int32 Value)
{
	SetCurrencyAmount(Value);
}

void UINV_InventoryViewModel::SetCurrencyAmount(float Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(CurrencyAmount, Value);
}

void UINV_InventoryViewModel::SetMaxItemsCapacity(int32 Value)
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
		for (const auto& ItemVM : Cat->GetCategoryItems())
		{
			if (ItemVM->GetItemIdentification().Id == ItemIdentification.Id)
			{
				return ItemVM;
			}
		}
	}

	return nullptr;
}