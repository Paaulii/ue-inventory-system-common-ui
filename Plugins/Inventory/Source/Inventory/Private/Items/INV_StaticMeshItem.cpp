// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_StaticMeshItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_StaticMeshItem::AINV_StaticMeshItem()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AINV_StaticMeshItem::ChangeMesh(FINV_ItemAssetDefinition* ItemAssetDefinition)
{
	if (FStaticItemData* StaticItemData = static_cast<FStaticItemData*>(ItemAssetDefinition))
	{
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent))
		{
			StaticMeshComponent->SetStaticMesh(StaticItemData->StaticMesh);
		}
	}
}