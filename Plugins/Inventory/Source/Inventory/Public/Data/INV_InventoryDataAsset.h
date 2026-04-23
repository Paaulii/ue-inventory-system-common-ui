#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/INV_InventoryDataAssetTypes.h"
#include "INV_InventoryDataAsset.generated.h"

UCLASS(Blueprintable)
class INVENTORY_API UINV_InventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FINV_CategoryDefinitionData> Categories = {};

	UPROPERTY(EditAnywhere)
	TArray<FINV_ItemAssetDefinition> Items = {};

	FINV_ItemAssetDefinition* GetItemAssetDefinition(const FGameplayTag& ItemTag, const FGameplayTag& CategoryTag);
};
