#include "Player/Data/INV_InventorySaveData.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"

void UINV_InventorySaveData::UpdateItemDataAtIndex(const FINV_ItemData& ItemData, int16 Index)
{
	if (Index < PlayerItems.Num())
	{
		PlayerItems[Index] = ItemData;
	}
	else
	{
		PlayerItems.Add(ItemData);
	}
}

void UINV_InventorySaveData::SetPlayerItems(const TArray<FINV_ItemData>& ItemsToSave) 
{
	PlayerItems = ItemsToSave;
}

void UINV_InventorySaveData::SetEquippedItems(const TArray<FINV_ItemIdentification>& EquippedItemsToSave)
{
	EquippedItems = EquippedItemsToSave;
}

void UINV_InventorySaveData::SetInventorySaveData(int32 PlayerCurrency, int16 ItemsCapacity, const TArray<FINV_ItemData>& Owned, const TArray<FINV_ItemIdentification>& Equipped)
{
	CurrencyAmount = PlayerCurrency;
	MaxItemsCapacity = ItemsCapacity;
	SetPlayerItems(Owned);
	SetEquippedItems(Equipped);
}
