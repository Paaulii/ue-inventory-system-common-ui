// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ItemData.h"
#include "GameFramework/SaveGame.h"
#include "INV_InventorySaveData.generated.h"

UCLASS()
class INVENTORY_API UINV_InventorySaveData : public USaveGame
{
	GENERATED_BODY()
public:
	TArray<FINV_ItemData> GetInventoryItems() {return PlayerItems;}
	void AddItemToArray(FINV_ItemData& ItemData);
protected:
	UPROPERTY()
	TArray<FINV_ItemData> PlayerItems;
};
