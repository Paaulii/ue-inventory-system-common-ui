#include "Data/INV_InventoryDataAsset.h"

FINV_ItemAssetDefinition* UINV_InventoryDataAsset::GetItemDefinition(int ItemId, int CategoryId)
{
	TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition = Items.FindByPredicate(
	[ItemId, CategoryId](const TInstancedStruct<FINV_ItemAssetDefinition>& Item)
	{
		FINV_ItemAssetDefinition ItemAssetDefinition = Item.Get();

		return ItemAssetDefinition.Id == ItemId && ItemAssetDefinition.CategoryId == CategoryId;
	});

	if (ItemAssetDefinition)
	{
		return ItemAssetDefinition->GetMutablePtr<FINV_ItemAssetDefinition>();
	}

	return nullptr;
}
