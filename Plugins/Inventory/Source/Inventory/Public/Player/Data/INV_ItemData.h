#pragma once
#include "CoreMinimal.h"
#include "INV_ItemData.generated.h"

USTRUCT(BlueprintType)
struct FINV_ItemData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	int32 CategoryId;

	UPROPERTY(EditDefaultsOnly)
	int32 Quantity;

	UPROPERTY()
	bool bIsEquipped;
};

