#pragma once

#include "CoreMinimal.h"
#include "CategoryData.h"
#include "InventoryData.generated.h"

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrencyAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxItemsCapacity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCategoryData> Categories;
};
