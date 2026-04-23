#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"

void FINV_InventoryDisplayData::SetCurrencyAmount(const int32 Amount)
{
	CurrencyAmount = Amount;
}

void FINV_InventoryDisplayData::AddOrUpdateItem(const FINV_ItemDisplayData& ItemToUpdate)
{
	for (auto& Category : Categories)
	{
		if (Category.Tag != ItemToUpdate.ItemIdentification.CategoryTag)
		{
			continue;
		}

		for (int32 i = 0; i < Category.Items.Num(); i++)
		{
			if (Category.Items[i].ItemIdentification.Id == ItemToUpdate.ItemIdentification.Id)
			{
				Category.Items[i] = ItemToUpdate;
				return;
			}
		}

		Category.Items.Add(ItemToUpdate);
	}
}

void FINV_InventoryDisplayData::RemoveItemAt(const int32 ItemId)
{
	for (auto& Category : Categories)
	{
		for (int32 i = 0; i < Category.Items.Num(); i++)
		{
			if (Category.Items[i].ItemIdentification.Id == ItemId)
			{
				Category.Items.RemoveAt(i);
				return;
			}
		}
	}
}

const FINV_CategoryDisplayData* FINV_InventoryDisplayData::GetCategory(const FGameplayTag& GameplayTag)
{
	for (const auto& Category : Categories)
	{
		if (Category.Tag == GameplayTag)
		{
			return &Category;
		}
	}

	return nullptr;
}
