#pragma once

#include "CoreMinimal.h"
#include "INV_CategoryData.h"
#include "INV_InventoryData.generated.h"

USTRUCT(BlueprintType)
struct FINV_InventoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrencyAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxItemsCapacity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FINV_CategoryData> Categories;
};
