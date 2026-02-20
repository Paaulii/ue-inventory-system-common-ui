#pragma once
#include "CoreMinimal.h"
#include "INV_ItemSaveDataTypes.generated.h"

USTRUCT()
struct FINV_ItemIdentificationData
{
	GENERATED_BODY()
	
	int32 Id;
	int32 CategoryId;
};


USTRUCT()
struct FINV_ItemSaveData
{
	GENERATED_BODY()
	
	FINV_ItemIdentificationData IdData;
	int32 Quantity;
};



