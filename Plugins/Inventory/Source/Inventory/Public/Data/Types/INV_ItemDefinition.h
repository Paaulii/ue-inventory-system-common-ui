#pragma once
#include "CoreMinimal.h"
#include "INV_ItemDefinition.generated.h"


USTRUCT()
struct FINV_ItemDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	int16 ItemId;
	
	UPROPERTY(EditInstanceOnly)
	int16 CategoryId;
};
