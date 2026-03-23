#pragma once

UENUM(BlueprintType)
enum class FINV_ItemActionType : uint8
{
	Drop,
	Consume,
	Equip,
	Unequip
};