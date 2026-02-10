#pragma once

#include "CoreMinimal.h"
#include "INV_ItemIdentificationData.generated.h"

USTRUCT(BlueprintType)
struct FINV_ItemIdentificationData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	int32 CategoryId;
};
