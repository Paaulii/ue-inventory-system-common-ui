// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StructUtils/InstancedStruct.h"
#include "INV_Equippable.generated.h"

struct FINV_ItemAssetDefinition;

UINTERFACE(MinimalAPI)
class UINV_Equippable : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IINV_Equippable
{
	GENERATED_BODY()
public:
	virtual void SetMesh(const TInstancedStruct<FINV_ItemAssetDefinition>* ItemDefinition) const = 0;
};
