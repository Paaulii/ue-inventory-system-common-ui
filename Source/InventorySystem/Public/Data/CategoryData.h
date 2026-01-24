#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "StructUtils/InstancedStruct.h"
#include "CategoryData.generated.h"

USTRUCT(BlueprintType)
struct FCategoryData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CategoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CategoryIcon = nullptr;

	UPROPERTY(EditAnywhere, meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FItemData>> Items;
};
