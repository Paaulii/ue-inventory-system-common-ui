// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_Item.h"
#include "INV_StaticMeshItem.generated.h"

UCLASS()
class INVENTORY_API AINV_StaticMeshItem : public AINV_Item
{
	GENERATED_BODY()

public:
	AINV_StaticMeshItem();
	virtual void ChangeMesh(FINV_ItemAssetDefinition* ItemDefinition) override;
};
