#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "INV_ItemSaveDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FINV_ItemIdentification
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 Id;
	
	UPROPERTY(EditInstanceOnly)
	FGameplayTag ItemTag;
	
	UPROPERTY(EditInstanceOnly)
	FGameplayTag CategoryTag;
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
		return Other.ItemIdentification.Id == ItemIdentification.Id;
	}
};

