#pragma once
#include "CoreMinimal.h"
#include "INV_ItemSaveDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FINV_ItemIdentification
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 UID;
	
	UPROPERTY(EditInstanceOnly)
	FName ItemId;
	
	UPROPERTY(EditInstanceOnly)
	FName CategoryId;
};

USTRUCT()
struct FINV_ItemData
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	FINV_ItemIdentification ItemIdentification;

	UPROPERTY(EditInstanceOnly)
	int16 Quantity;

	bool operator==(const FINV_ItemData & Other) const
	{
		return Other.ItemIdentification.UID == ItemIdentification.UID;
	}
};

