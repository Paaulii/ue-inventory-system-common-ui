#include "Items/INV_StaticEquippedItem.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_StaticEquippedItem::AINV_StaticEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	SetActorEnableCollision(false);
}

void AINV_StaticEquippedItem::SetMesh(const FINV_ItemAssetDefinition* ItemDefinition) const
{
	if (ItemDefinition->StaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(ItemDefinition->StaticMesh);

		if (ItemDefinition->Material)
		{
			StaticMeshComponent->SetMaterial(0, ItemDefinition->Material);
		}
	}
}
