// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_ItemViewModel.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"

void UINV_ItemViewModel::Initialize(const FINV_ItemDisplayData& ItemData, UINV_CategoryViewModel* CategoryVM)
{
	SetItemName(ItemData.Name);
	SetDescription(ItemData.Description);
	SetSmallImage(ItemData.SmallImage);
	SetLargeImage(ItemData.LargeImage);
	SetRarity(ItemData.Rarity);
	SetCurrencyValue(ItemData.CurrencyValue);
	SetIsEquipped(false);
	SetCategory(CategoryVM);
	SetRequiredLevel(ItemData.RequiredLevel);
	SetQuantity(ItemData.Quantity);
	SetMaxQuantity(ItemData.MaxQuantity);
	SetConsumable(ItemData.bIsConsumable);
	SetEquippable(ItemData.bIsEquippable);
	SetDroppable(ItemData.bIsDroppable);

	ItemIdentification = ItemData.ItemIdentification;
}

bool UINV_ItemViewModel::IsQuantityVisible() const
{
	return MaxQuantity > 1;
}

void UINV_ItemViewModel::SetItemName(const FText& Name)
{
	UE_MVVM_SET_PROPERTY_VALUE(ItemName, Name);
}

void UINV_ItemViewModel::SetDescription(const FText& NewDescription)
{
	UE_MVVM_SET_PROPERTY_VALUE(Description, NewDescription);
}

void UINV_ItemViewModel::SetSmallImage(UTexture2D* Image)
{
	UE_MVVM_SET_PROPERTY_VALUE(SmallImage, Image);
}

void UINV_ItemViewModel::SetLargeImage(UTexture2D* Image)
{
	UE_MVVM_SET_PROPERTY_VALUE(LargeImage, Image);
}

void UINV_ItemViewModel::SetRarity(const EINV_ItemRarity& ItemRarity)
{
	UE_MVVM_SET_PROPERTY_VALUE(Rarity, ItemRarity);
}

void UINV_ItemViewModel::SetCurrencyValue(const int32 Currency)
{
	UE_MVVM_SET_PROPERTY_VALUE(CurrencyValue, Currency);
}

void UINV_ItemViewModel::SetIsEquipped(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(IsEquipped, bState);
}

void UINV_ItemViewModel::SetCategory(UINV_CategoryViewModel* CategoryVM)
{
	UE_MVVM_SET_PROPERTY_VALUE(Category, CategoryVM);
}

void UINV_ItemViewModel::SetRequiredLevel(int32 Level)
{
	UE_MVVM_SET_PROPERTY_VALUE(RequiredLevel, Level);
}

void UINV_ItemViewModel::SetQuantity(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Quantity, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsQuantityVisible);
	}
}

void UINV_ItemViewModel::SetMaxQuantity(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxQuantity, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsQuantityVisible);
	}
}

void UINV_ItemViewModel::SetEquippable(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(Equippable, bState);
}

void UINV_ItemViewModel::SetConsumable(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(Consumable, bState);
}

void UINV_ItemViewModel::SetDroppable(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(Droppable, bState);
}
