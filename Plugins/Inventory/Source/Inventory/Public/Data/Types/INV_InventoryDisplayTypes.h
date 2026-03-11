#pragma once

#include "CoreMinimal.h"
#include "INV_InventoryDataAssetTypes.h"
#include "INV_InventoryDisplayTypes.generated.h"

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

	void UpdateItem(const FINV_ItemDisplayData& ItemToUpdate);
	void RemoveItemAt(const int16 SaveDataIndex);
};

USTRUCT()
struct FINV_CategoryDisplayData
{
	GENERATED_BODY()
	FINV_CategoryDisplayData(){}
	FINV_CategoryDisplayData(const FName& Id, const FText& Name, const TArray<FINV_ItemDisplayData>& Items): Id(Id), CategoryName(Name), Items(Items){}

	FName Id;
	FText CategoryName;
	TArray<FINV_ItemDisplayData> Items;

	void AddItemToCategory(FINV_ItemDisplayData* ItemDisplayData);
};

USTRUCT()
struct FINV_ItemDisplayData
{
	GENERATED_BODY()
	FINV_ItemDisplayData(): SaveDataIndex(-1), SmallImage(nullptr), LargeImage(nullptr),
	Rarity(EINV_ItemRarity::Common), CurrencyValue(0), RequiredLevel(0), Quantity(0),MaxQuantity(0),
	bIsConsumable(false), bIsEquippable(false),bIsDroppable(false){}
	
	FINV_ItemDisplayData(int16 SaveDataIndex, const FINV_ItemAssetDefinition* AssetDefinition, int32 Quantity)
	{
		this->SaveDataIndex = SaveDataIndex;
		Id = AssetDefinition->Id;
		CategoryId = AssetDefinition->CategoryId;
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
	}
	
	int16 SaveDataIndex;
	FName Id;
	FName CategoryId;
	FText Name;
	FText Description;
	
	UPROPERTY()
	UTexture2D* SmallImage;
	
	UPROPERTY()
	UTexture2D* LargeImage;
	
	EINV_ItemRarity Rarity;
	int32 CurrencyValue;
	int32 RequiredLevel;
	int32 Quantity;
	int32 MaxQuantity;
	
	bool bIsConsumable;
	bool bIsEquippable;
	bool bIsDroppable;
};
