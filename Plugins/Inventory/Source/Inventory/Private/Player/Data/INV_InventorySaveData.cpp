#include "Player/Data/INV_InventorySaveData.h"

void UINV_InventorySaveData::AddItemToArray(FINV_ItemData& ItemData)
{
	bool bItemFound = false;
	
	for (FINV_ItemData& PlayerItemData: PlayerItems)
	{
		if (ItemData.Id == PlayerItemData.Id &&
			ItemData.CategoryId == PlayerItemData.CategoryId)
		{
			bItemFound = true;
			PlayerItemData.Quantity += ItemData.Quantity;
		}
	}

	if (!bItemFound)
	{
		PlayerItems.Add(ItemData);
	}
}
