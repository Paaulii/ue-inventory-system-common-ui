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
	FINV_ItemDisplayData(const FINV_ItemIdentification& ItemIdentification, const FINV_ItemAssetDefinition* AssetDefinition, int32 Quantity)
		: ItemIdentification(ItemIdentification), Quantity(Quantity)
	{
		// todo: create base class from FINV_ItemAssetDefinition and pass as argument in constructor, pass as reference
		Name = AssetDefinition->Name;
		Description = AssetDefinition->Description;
		SmallImage = AssetDefinition->SmallImage;
		LargeImage = AssetDefinition->LargeImage;
		Rarity = AssetDefinition->Rarity;
		CurrencyValue = AssetDefinition->CurrencyValue;
		RequiredLevel = AssetDefinition->RequiredLevel;
		MaxQuantity = AssetDefinition->MaxQuantity;
		bIsConsumable = AssetDefinition->bIsConsumable;
		bIsEquippable = AssetDefinition->bIsEquippable;
		bIsDroppable = AssetDefinition->bIsDroppable;
		EquipType = AssetDefinition->EquipType;
	}
	
	bool operator==(const FINV_ItemDisplayData& Other) const
	{
		return ItemIdentification.Id == Other.ItemIdentification.Id;
	}

	FINV_ItemIdentification ItemIdentification {};
	FText Name {};
	FText Description {};
	
	UPROPERTY()
	TObjectPtr<UTexture2D> SmallImage = nullptr;
	
	UPROPERTY()
	TObjectPtr<UTexture2D> LargeImage = nullptr;
	
	EINV_ItemRarity Rarity = EINV_ItemRarity::Common;
	EINV_ItemEquipType EquipType = EINV_ItemEquipType::None;
	
	int32 CurrencyValue = 0;
	int32 RequiredLevel = 0;
	int32 Quantity = 0;
	int32 MaxQuantity = 0;
	
	bool bIsConsumable = false;
	bool bIsEquippable = false;
	bool bIsDroppable = false;
	bool bIsEquipped = false;
};
