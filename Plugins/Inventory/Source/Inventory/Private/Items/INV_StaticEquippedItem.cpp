#include "Items/INV_StaticEquippedItem.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_StaticEquippedItem::AINV_StaticEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneRoot);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	SetActorEnableCollision(false);
}

void AINV_StaticEquippedItem::SetMesh(const FINV_ItemAssetDefinition* ItemDefinition, USkeletalMeshComponent* ParentMeshComponent) const
{
	if (ensureMsgf(ItemDefinition, TEXT("Couldn't find item's definition. Cannot set skeletal mesh for item.")))
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
}
