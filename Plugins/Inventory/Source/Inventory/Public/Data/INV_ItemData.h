#pragma once
#include "CoreMinimal.h"
#include "INV_ItemIdentificationData.h"
#include "INV_ItemData.generated.h"

USTRUCT(BlueprintType)
struct FINV_ItemData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FINV_ItemIdentificationData IdData;
	
	UPROPERTY(EditDefaultsOnly)
	int32 Quantity;
};

