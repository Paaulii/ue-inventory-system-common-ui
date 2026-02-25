// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_Item.h"
#include "INV_SkeletalMeshItem.generated.h"

UCLASS()
class INVENTORY_API AINV_SkeletalMeshItem : public AINV_Item
{
	GENERATED_BODY()

public:
	AINV_SkeletalMeshItem();
	virtual void ChangeMesh(TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition) override;
};
