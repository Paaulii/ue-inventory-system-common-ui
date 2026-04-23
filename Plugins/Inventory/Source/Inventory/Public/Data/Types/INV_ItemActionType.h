#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FINV_ItemActionType : uint8
{
	None,
	Drop,
	Consume,
	Equip,
	Unequip,
	Sell
};