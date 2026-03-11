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
