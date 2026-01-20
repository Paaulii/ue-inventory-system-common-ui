#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "StructUtils/InstancedStruct.h"
#include "CategoryInfo.generated.h"

USTRUCT(BlueprintType)
struct FCategoryInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CategoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CategoryIcon;

	UPROPERTY(EditAnywhere, meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FItemData>> Items;
};
