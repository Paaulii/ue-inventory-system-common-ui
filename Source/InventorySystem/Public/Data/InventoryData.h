#pragma once

#include "CoreMinimal.h"
#include "CategoryData.h"
#include "InventoryData.generated.h"

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()
	
	int CurrencyAmount;
	TArray<FCategoryData> Categories;
};
