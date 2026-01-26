// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Engine/DataAsset.h"
#include "DebugInventoryData.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UDebugInventoryData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventoryData InventoryData;
};
