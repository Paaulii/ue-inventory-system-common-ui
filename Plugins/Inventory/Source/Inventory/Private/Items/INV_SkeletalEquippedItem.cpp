// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_SkeletalEquippedItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"


AINV_SkeletalEquippedItem::AINV_SkeletalEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetActorEnableCollision(false);
}

void AINV_SkeletalEquippedItem::SetMesh(const FINV_ItemAssetDefinition* ItemDefinition) const
{
	if (ItemDefinition->SkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(ItemDefinition->SkeletalMesh);

		if (ItemDefinition->Material)
		{
			SkeletalMeshComponent->SetMaterial(0, ItemDefinition->Material);
		}
	}
}

