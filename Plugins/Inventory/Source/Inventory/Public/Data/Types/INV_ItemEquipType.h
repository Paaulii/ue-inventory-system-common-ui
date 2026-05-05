#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EINV_ItemEquipType : uint8
{
	None,
	Helmet,
	Chest,
	Legs,
	Boots,
	Gloves,
	Weapon
};