#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "INV_ItemSaveDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FINV_ItemIdentification
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 Id = 0;
	
	UPROPERTY(EditInstanceOnly)
	FGameplayTag ItemTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditInstanceOnly)
	FGameplayTag CategoryTag = FGameplayTag::EmptyTag;
};

USTRUCT()
struct FINV_ItemData
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	FINV_ItemIdentification ItemIdentification = {};

	UPROPERTY(EditInstanceOnly)
	int32 Quantity = 0;

	bool operator==(const FINV_ItemData& Other) const
	{
		return Other.ItemIdentification.Id == ItemIdentification.Id;
	}
};

