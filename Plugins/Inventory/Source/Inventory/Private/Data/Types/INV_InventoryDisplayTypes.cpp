#include "Data/Types/INV_InventoryDisplayTypes.h"

void FINV_InventoryDisplayData::UpdateItem(const FINV_ItemDisplayData& ItemToUpdate)
{
	for (FINV_CategoryDisplayData& Category : Categories)
	{
		if (Category.Id != ItemToUpdate.CategoryId)
		{
			continue;
		}

		for (int i = 0; i < Category.Items.Num(); i++ ) 
		{
			if (Category.Items[0].Id == ItemToUpdate.Id && Category.Items[0].SaveDataIndex == ItemToUpdate.SaveDataIndex)
			{
				Category.Items[i] = ItemToUpdate;
				return;
			}
		}

		Category.Items.Add(ItemToUpdate);
	}
}


