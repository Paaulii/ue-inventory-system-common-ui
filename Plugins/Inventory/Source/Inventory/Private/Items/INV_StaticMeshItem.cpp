#include "Items/INV_StaticMeshItem.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_StaticMeshItem::AINV_StaticMeshItem()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
}

void AINV_StaticMeshItem::ChangeMesh(const FINV_ItemAssetDefinition* ItemAssetDefinition)
{
	if (ensureMsgf(ItemAssetDefinition, TEXT("Couldn't find item's definition. Cannot set static mesh for item.")))
	{
		if (ItemAssetDefinition->StaticMesh)
		{
			if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent))
			{
				StaticMeshComponent->SetStaticMesh(ItemAssetDefinition->StaticMesh);

				if (ItemAssetDefinition->Material)
				{
					StaticMeshComponent->SetMaterial(0, ItemAssetDefinition->Material);
				}
			}
		}
	}
}