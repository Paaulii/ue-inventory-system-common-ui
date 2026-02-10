#include "Player/Data/INV_InventorySaveData.h"


void UINV_InventorySaveData::AddItemToArray(FINV_ItemData& ItemData)
{
	bool bItemFound = false;
	
	for (FINV_ItemData& PlayerItemData: PlayerItems)
	{
		if (ItemData.IdData.Id == PlayerItemData.IdData.Id &&
			ItemData.IdData.CategoryId == PlayerItemData.IdData.CategoryId)
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
