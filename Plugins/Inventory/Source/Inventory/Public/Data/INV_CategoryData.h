#pragma once

#include "CoreMinimal.h"
#include "INV_ItemData.h"
#include "StructUtils/InstancedStruct.h"
#include "INV_CategoryData.generated.h"

USTRUCT(BlueprintType)
struct FINV_CategoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CategoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CategoryIcon = nullptr;

	UPROPERTY(EditAnywhere, meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FINV_ItemData>> Items;
};
