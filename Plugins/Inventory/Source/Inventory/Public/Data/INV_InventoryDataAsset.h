// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types/INV_InventoryDataAssetTypes.h"
#include "Engine/DataAsset.h"
#include "INV_InventoryDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORY_API UINV_InventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FINV_CategoryDefinitionData> Categories;

	UPROPERTY(EditAnywhere, meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FINV_ItemAssetDefinition>> Items;

	FINV_ItemAssetDefinition* GetItemDefinition(FName ItemId, FName CategoryId);
	TInstancedStruct<FINV_ItemAssetDefinition>* GetInstancedItemDefinition(FName ItemId, FName CategoryId);
};
