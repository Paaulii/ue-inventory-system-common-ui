// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_EquipmentViewModel.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_EquipmentViewModel::OnEquipItem(UINV_ItemViewModel& EquippedItem)
{
	EquippedItem.SetIsEquipped(true);
	EquippedItems.Add(&EquippedItem);
	SetLastEquippedItem(&EquippedItem);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(EquippedItems);
}

void UINV_EquipmentViewModel::OnUnequipItem(UINV_ItemViewModel& UnequippedItem)
{
	int32 ItemToDeleteIndex = EquippedItems.IndexOfByPredicate([&UnequippedItem](const UINV_ItemViewModel* ItemVM)
	{
		return ItemVM->GetItemIdentification().Id == UnequippedItem.GetItemIdentification().Id;
	});

	if (ItemToDeleteIndex >= 0)
	{
		UnequippedItem.SetIsEquipped(false);
		SetLastUnequippedItem(&UnequippedItem);
		EquippedItems.RemoveAt(ItemToDeleteIndex);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(EquippedItems);
	}
}

void UINV_EquipmentViewModel::SetLastEquippedItem(UINV_ItemViewModel* EquippedItem)
{
	UE_MVVM_SET_PROPERTY_VALUE(LastEquippedItem, EquippedItem);

	if (LastEquippedItem == LastUnequippedItem)
	{
		SetLastUnequippedItem(nullptr);
	}
}

void UINV_EquipmentViewModel::SetLastUnequippedItem(UINV_ItemViewModel* UnequippedItem)
{
	UE_MVVM_SET_PROPERTY_VALUE(LastUnequippedItem, UnequippedItem);

	if (LastEquippedItem == LastUnequippedItem)
	{
		SetLastEquippedItem(nullptr);
	}
}
