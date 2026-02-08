// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_InventoryData.h"
#include "Engine/DataAsset.h"
#include "INV_DebugInventoryData.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_DebugInventoryData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FINV_InventoryData InventoryData;
};
