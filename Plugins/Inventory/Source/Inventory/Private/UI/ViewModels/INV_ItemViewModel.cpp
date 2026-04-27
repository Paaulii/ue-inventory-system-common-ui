#include "UI/ViewModels/INV_ItemViewModel.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"

void UINV_ItemViewModel::Initialize(const FINV_ItemDisplayData& ItemData, UINV_CategoryViewModel* CategoryVM)
{
	UE_MVVM_SET_PROPERTY_VALUE(ItemName, ItemData.ItemDetails.Name);
	UE_MVVM_SET_PROPERTY_VALUE(Description, ItemData.ItemDetails.Description);
	UE_MVVM_SET_PROPERTY_VALUE(SmallImage, ItemData.ItemDetails.SmallImage);
	UE_MVVM_SET_PROPERTY_VALUE(LargeImage, ItemData.ItemDetails.LargeImage);
	UE_MVVM_SET_PROPERTY_VALUE(Rarity, ItemData.ItemDetails.Rarity);
	UE_MVVM_SET_PROPERTY_VALUE(CurrencyValue, ItemData.ItemDetails.CurrencyValue);
	UE_MVVM_SET_PROPERTY_VALUE(Category, CategoryVM);
	UE_MVVM_SET_PROPERTY_VALUE(RequiredLevel, ItemData.ItemDetails.RequiredLevel);
	UE_MVVM_SET_PROPERTY_VALUE(Quantity, ItemData.Quantity);
	UE_MVVM_SET_PROPERTY_VALUE(MaxQuantity, ItemData.ItemDetails.MaxQuantity);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(VM_IsQuantityVisible);
	UE_MVVM_SET_PROPERTY_VALUE(bIsConsumable, ItemData.ItemDetails.bIsConsumable);
	UE_MVVM_SET_PROPERTY_VALUE(bIsEquippable, ItemData.ItemDetails.bIsEquippable);
	UE_MVVM_SET_PROPERTY_VALUE(bIsDroppable, ItemData.ItemDetails.bIsDroppable);
	UE_MVVM_SET_PROPERTY_VALUE(EquipType, ItemData.ItemDetails.EquipType);
	SetbIsEquipped(ItemData.bIsEquipped);
	ItemIdentification = ItemData.ItemIdentification;
}

bool UINV_ItemViewModel::VM_IsQuantityVisible() const
{
	return MaxQuantity > 1;
}

void UINV_ItemViewModel::SetbIsEquipped(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsEquipped,bState);
}
