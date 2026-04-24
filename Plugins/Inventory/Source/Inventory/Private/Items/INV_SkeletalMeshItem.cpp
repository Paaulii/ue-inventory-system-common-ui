#include "Items/INV_SkeletalMeshItem.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_SkeletalMeshItem::AINV_SkeletalMeshItem()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
}

void AINV_SkeletalMeshItem::ChangeMesh(const FINV_ItemAssetDefinition* ItemAssetDefinition)
{
	if (ensureMsgf(ItemAssetDefinition, TEXT("Couldn't find item's definition. Cannot set skeletal mesh for item.")))
	{
		if (ItemAssetDefinition->SkeletalMesh)
		{
			if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent))
			{
				SkeletalMeshComponent->SetSkeletalMesh(ItemAssetDefinition->SkeletalMesh);

				if (ItemAssetDefinition->Material)
				{
					SkeletalMeshComponent->SetMaterial(0, ItemAssetDefinition->Material);
				}
			}
		}
	}
}

