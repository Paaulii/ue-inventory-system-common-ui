#include "Data/INV_InventoryDataAsset.h"

FINV_ItemAssetDefinition* UINV_InventoryDataAsset::GetItemDefinition(const FGameplayTag& ItemTag, const FGameplayTag& CategoryTag)
{
	TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinitionRef = GetInstancedItemDefinition(ItemTag, CategoryTag);
	return ItemAssetDefinitionRef ? ItemAssetDefinitionRef->GetMutablePtr<FINV_ItemAssetDefinition>() : nullptr;
}

TInstancedStruct<FINV_ItemAssetDefinition>* UINV_InventoryDataAsset::GetInstancedItemDefinition(const FGameplayTag& ItemTag, const FGameplayTag& CategoryTag)
{
	TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition = Items.FindByPredicate(
		[ItemTag, CategoryTag](const TInstancedStruct<FINV_ItemAssetDefinition>& Item)
		{
			FINV_ItemAssetDefinition ItemAssetDefinition = Item.Get();

			return ItemAssetDefinition.ItemTag == ItemTag && ItemAssetDefinition.CategoryTag == CategoryTag;
		});

	return ItemAssetDefinition;
}
