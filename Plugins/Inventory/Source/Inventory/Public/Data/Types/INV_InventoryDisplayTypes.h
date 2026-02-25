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
	FINV_InventoryDisplayData(int32 CurrencyAmount, int32 MaxItemsCapacity, TArray<FINV_CategoryDisplayData>& Categories)
	:CurrencyAmount(CurrencyAmount), MaxItemsCapacity(MaxItemsCapacity),Categories(Categories){}

	int32 CurrencyAmount;
	int32 MaxItemsCapacity;
	TArray<FINV_CategoryDisplayData> Categories;
};

USTRUCT()
struct FINV_CategoryDisplayData
{
	GENERATED_BODY()
	FINV_CategoryDisplayData(){}
	FINV_CategoryDisplayData(const FText& Name, const TArray<FINV_ItemDisplayData>& Items): CategoryName(Name), Items(Items){}
	
	FText CategoryName;
	TArray<FINV_ItemDisplayData> Items;
};

USTRUCT()
struct FINV_ItemDisplayData
{
	GENERATED_BODY()
	FINV_ItemDisplayData(): Id(0), SmallImage(nullptr), LargeImage(nullptr),
	Rarity(EINV_ItemRarity::Common), CurrencyValue(0), RequiredLevel(0), Stacks(0){}
	
	FINV_ItemDisplayData(const FINV_ItemAssetDefinition* AssetDefinition, int32 Stacks)
	{
		Id = AssetDefinition->Id;
		Name = AssetDefinition->Name;
		Description = AssetDefinition->Description;
		SmallImage = AssetDefinition->SmallImage;
		LargeImage = AssetDefinition->LargeImage;
		Rarity = AssetDefinition->Rarity;
		CurrencyValue = AssetDefinition->CurrencyValue;
		RequiredLevel = AssetDefinition->RequiredLevel;
		this->Stacks = Stacks;
	}
	
	
	int32 Id;
	FText Name;
	FText Description;
	
	UPROPERTY()
	UTexture2D* SmallImage;
	
	UPROPERTY()
	UTexture2D* LargeImage;
	
	EINV_ItemRarity Rarity;
	int32 CurrencyValue;
	int32 RequiredLevel;
	int32 Stacks;
};
