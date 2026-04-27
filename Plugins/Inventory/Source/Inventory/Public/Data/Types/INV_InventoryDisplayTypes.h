#pragma once
#include "CoreMinimal.h"
#include "INV_InventoryDataAssetTypes.h"
#include "INV_ItemSaveDataTypes.h"
#include "INV_InventoryDisplayTypes.generated.h"

enum class EINV_ItemRarity : uint8;
struct FINV_CategoryDisplayData;
struct FINV_ItemDisplayData;
struct FINV_ItemIdentification;

USTRUCT()
struct FINV_InventoryDisplayData
{
	GENERATED_BODY()
	FINV_InventoryDisplayData(){};
	FINV_InventoryDisplayData(const int32 CurrencyAmount, const int32 MaxItemsCapacity, const TArray<FINV_CategoryDisplayData>&& Categories)
		: CurrencyAmount(CurrencyAmount), MaxItemsCapacity(MaxItemsCapacity), Categories(Categories) {}
	
	void SetCurrencyAmount(const int32 Amount);
	void AddOrUpdateItem(const FINV_ItemDisplayData& ItemToUpdate);
	void RemoveItemAt(const int32 ItemId);
	const FINV_CategoryDisplayData* GetCategory(const FGameplayTag& GameplayTag);

	int32 CurrencyAmount = 0;
	int32 MaxItemsCapacity = 0;
	TArray<FINV_CategoryDisplayData> Categories = {};
};

USTRUCT()
struct FINV_CategoryDisplayData
{
	GENERATED_BODY()
	FINV_CategoryDisplayData(){};
	FINV_CategoryDisplayData(const FGameplayTag& Tag, const FText& Name, TArray<FINV_ItemDisplayData>&& Items)
		: Tag(Tag), CategoryName(Name), Items(Items) {}

	void AddItemToCategory(FINV_ItemDisplayData* ItemDisplayData);
	
	FGameplayTag Tag = FGameplayTag::EmptyTag;
	FText CategoryName = {};
	TArray<FINV_ItemDisplayData> Items = {};
};

USTRUCT()
struct FINV_ItemDisplayData
{
	GENERATED_BODY()
	FINV_ItemDisplayData(){}
	FINV_ItemDisplayData(const FINV_ItemIdentification& ItemIdentification, const FINV_ItemDetailsData& ItemDetails, int32 Quantity)
		: ItemIdentification(ItemIdentification), ItemDetails(ItemDetails), Quantity(Quantity){}
	
	bool operator==(const FINV_ItemDisplayData& Other) const
	{
		return ItemIdentification.Id == Other.ItemIdentification.Id;
	}

	FINV_ItemIdentification ItemIdentification = {};
	FINV_ItemDetailsData ItemDetails = {};
	int32 Quantity = 0;
	bool bIsEquipped = false;
};
