#include "Data/Types/INV_InventoryDisplayTypes.h"

#include "Data/Types/INV_ItemSaveDataTypes.h"

void FINV_InventoryDisplayData::UpdateItem(const FINV_ItemDisplayData& ItemToUpdate)
{
	for (FINV_CategoryDisplayData& Category : Categories)
	{
		if (Category.Id != ItemToUpdate.ItemIdentification.CategoryId)
		{
			continue;
		}

		for (int i = 0; i < Category.Items.Num(); i++)
		{
			if (Category.Items[i].ItemIdentification.UID == ItemToUpdate.ItemIdentification.UID)
			{
				Category.Items[i] = ItemToUpdate;
				return;
			}
		}

		Category.Items.Add(ItemToUpdate);
	}
}

void FINV_InventoryDisplayData::RemoveItemAt(const int16 ItemUID)
{
	for (FINV_CategoryDisplayData& Category : Categories)
	{
		for (int i = 0; i < Category.Items.Num(); i++)
		{
			if (Category.Items[i].ItemIdentification.UID == ItemUID)
			{
				Category.Items.RemoveAt(i);
				return;
			}
		}
	}
}