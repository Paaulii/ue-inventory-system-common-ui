#include "Data/INV_InventoryDataAsset.h"

FINV_ItemAssetDefinition* UINV_InventoryDataAsset::GetItemAssetDefinition(const FGameplayTag& ItemTag, const FGameplayTag& CategoryTag)
{
	FINV_ItemAssetDefinition* ItemAssetDefinition = Items.FindByPredicate(
		[ItemTag, CategoryTag](const FINV_ItemAssetDefinition& Item)
		{
			return Item.ItemTag == ItemTag && Item.CategoryTag == CategoryTag;
		});

	return ItemAssetDefinition;
}
