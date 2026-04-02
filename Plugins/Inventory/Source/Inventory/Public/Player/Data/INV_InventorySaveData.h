// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "INV_InventorySaveData.generated.h"

struct FINV_ItemIdentification;
struct FINV_ItemData;

UCLASS()
class INVENTORY_API UINV_InventorySaveData : public USaveGame
{
	GENERATED_BODY()
public:
	TArray<FINV_ItemData>& GetInventoryItems() {return PlayerItems;}
	TArray<FINV_ItemIdentification>& GetEquippedItems() {return EquippedItems;}
	int16 GetCurrencyAmount() const {return CurrencyAmount;}
	int16 GetMaxItemsCapacity() const {return MaxItemsCapacity;}
	void UpdateItemDataAtIndex(const FINV_ItemData& ItemData, int16 Index);
	void SetPlayerItems(const TArray<FINV_ItemData>& PlayerItems);
	void SetEquippedItems(const TArray<FINV_ItemIdentification>& EquippedItemsToSave);
	void SetInventorySaveData(int32 PlayerCurrency, int16 ItemsCapacity, const TArray<FINV_ItemData>& OwnedItems, const TArray<FINV_ItemIdentification>& Equipped );
	void SetCurrencyAmount(int32 Amount);
protected:
	UPROPERTY()
	int32 CurrencyAmount;
	
	UPROPERTY()
	int16 MaxItemsCapacity;

	UPROPERTY()
	TArray<FINV_ItemData> PlayerItems;
	
	UPROPERTY()
	TArray<FINV_ItemIdentification> EquippedItems;
};
