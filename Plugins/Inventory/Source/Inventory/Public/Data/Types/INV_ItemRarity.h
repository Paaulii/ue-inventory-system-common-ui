#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EINV_ItemRarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary,
	Mythic
};