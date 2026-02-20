// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "INV_InventorySaveData.generated.h"

struct FINV_ItemIdentificationData;
struct FINV_ItemSaveData;

UCLASS()
class INVENTORY_API UINV_InventorySaveData : public USaveGame
{
	GENERATED_BODY()
public:
	TArray<FINV_ItemSaveData> GetInventoryItems() {return PlayerItems;}
	int32 GetCurrencyAmount() const {return CurrencyAmount;}
	int32 GetMaxItemsCapacity() const {return MaxItemsCapacity;}
	void AddItemToArray(FINV_ItemSaveData& ItemData);
protected:
	UPROPERTY()
	int32 CurrencyAmount;
	
	UPROPERTY()
	int32 MaxItemsCapacity;
	
	UPROPERTY()
	TArray<FINV_ItemSaveData> PlayerItems;

	UPROPERTY()
	TArray<FINV_ItemIdentificationData> EquippedItems;
};
