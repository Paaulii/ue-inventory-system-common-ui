#include "Player/Data/INV_InventorySaveData.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"

void UINV_InventorySaveData::AddItemToArray(FINV_ItemSaveData& ItemData)
{
	bool bItemFound = false;
	
	for (FINV_ItemSaveData& PlayerItemData: PlayerItems)
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
