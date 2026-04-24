#include "Items/INV_SkeletalEquippedItem.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_SkeletalEquippedItem::AINV_SkeletalEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
	SetActorEnableCollision(false);
}

void AINV_SkeletalEquippedItem::SetMesh(const FINV_ItemAssetDefinition* ItemDefinition) const
{
	if (ensureMsgf(ItemDefinition, TEXT("Couldn't find item's definition. Cannot set skeletal mesh for equipped item.")))
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
}

