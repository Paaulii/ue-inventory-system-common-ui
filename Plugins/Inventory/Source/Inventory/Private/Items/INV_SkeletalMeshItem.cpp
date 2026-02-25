// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_SkeletalMeshItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"


AINV_SkeletalMeshItem::AINV_SkeletalMeshItem()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
}

void AINV_SkeletalMeshItem::ChangeMesh(FINV_ItemAssetDefinition* ItemAssetDefinition)
{
	if (FSkeletalItemData* SkeletalItemData = static_cast<FSkeletalItemData*>(ItemAssetDefinition))
	{
		if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent))
		{
			SkeletalMeshComponent->SetSkeletalMesh(SkeletalItemData->SkeletalMesh);
			SkeletalMeshComponent->SetMaterial(0, SkeletalItemData->Material);
		}
	}
}

