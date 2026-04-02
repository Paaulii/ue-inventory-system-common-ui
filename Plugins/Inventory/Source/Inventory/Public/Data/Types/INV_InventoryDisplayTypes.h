#pragma once

#include "CoreMinimal.h"
#include "INV_InventoryDataAssetTypes.h"
#include "INV_ItemSaveDataTypes.h"
#include "INV_InventoryDisplayTypes.generated.h"

struct FINV_ItemIdentification;
struct FINV_CategoryDisplayData;
struct FINV_ItemDisplayData;
enum class EINV_ItemRarity : uint8;

USTRUCT()
struct FINV_InventoryDisplayData
{
	GENERATED_BODY()
	FINV_InventoryDisplayData(): CurrencyAmount(0), MaxItemsCapacity(0){}
	FINV_InventoryDisplayData(const int32 CurrencyAmount, const int32 MaxItemsCapacity, const TArray<FINV_CategoryDisplayData>& Categories)
	:CurrencyAmount(CurrencyAmount), MaxItemsCapacity(MaxItemsCapacity),Categories(Categories){}

	int32 CurrencyAmount;
	int32 MaxItemsCapacity;
	TArray<FINV_CategoryDisplayData> Categories;

	void SetCurrencyAmount(const int32 Amount);
	void AddOrUpdateItem(const FINV_ItemDisplayData& ItemToUpdate);
	void RemoveItemAt(const int16 ItemId);
	const FINV_CategoryDisplayData* GetCategory(const FGameplayTag& GameplayTag);
};

USTRUCT()
struct FINV_CategoryDisplayData
{
	GENERATED_BODY()
	FINV_CategoryDisplayData(){}
	FINV_CategoryDisplayData(const FGameplayTag& Tag, const FText& Name, const TArray<FINV_ItemDisplayData>& Items):
	Tag(Tag), CategoryName(Name), Items(Items){}

	FGameplayTag Tag;
	FText CategoryName;
	TArray<FINV_ItemDisplayData> Items;

	void AddItemToCategory(FINV_ItemDisplayData* ItemDisplayData);
};

USTRUCT()
struct FINV_ItemDisplayData
{
	GENERATED_BODY()
	FINV_ItemDisplayData(){}
	FINV_ItemDisplayData(const FINV_ItemIdentification& ItemIdentification, const FINV_ItemAssetDefinition* AssetDefinition, int32 Quantity)
	{
		this->ItemIdentification = ItemIdentification;
		Name = AssetDefinition->Name;
		Description = AssetDefinition->Description;
		SmallImage = AssetDefinition->SmallImage;
		LargeImage = AssetDefinition->LargeImage;
		Rarity = AssetDefinition->Rarity;
		CurrencyValue = AssetDefinition->CurrencyValue;
		RequiredLevel = AssetDefinition->RequiredLevel;
		MaxQuantity = AssetDefinition->MaxQuantity;
		this->Quantity = Quantity;
		bIsConsumable = AssetDefinition->bIsConsumable;
		bIsEquippable = AssetDefinition->bIsEquippable;
		bIsDroppable = AssetDefinition->bIsDroppable;
		EquipType = AssetDefinition->EquipType;
	}
	
	bool operator==(const FINV_ItemDisplayData & Other) const
	{
		return ItemIdentification.Id == Other.ItemIdentification.Id;
	}

	FINV_ItemIdentification ItemIdentification {};
	FText Name {};
	FText Description {};
	
	UPROPERTY()
	UTexture2D* SmallImage {nullptr};
	
	UPROPERTY()
	UTexture2D* LargeImage {nullptr};
	
	EINV_ItemRarity Rarity {EINV_ItemRarity::Common};
	EINV_ItemEquipType EquipType {EINV_ItemEquipType::None};
	
	int32 CurrencyValue {0};
	int32 RequiredLevel {0};
	int32 Quantity {0};
	int32 MaxQuantity {0};
	
	bool bIsConsumable {false};
	bool bIsEquippable {false};
	bool bIsDroppable {false};
	bool bIsEquipped {false};
};
