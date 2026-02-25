// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_StaticMeshItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_StaticMeshItem::AINV_StaticMeshItem()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AINV_StaticMeshItem::ChangeMesh(TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition)
{
	if (ItemAssetDefinition->GetScriptStruct() == FStaticItemData::StaticStruct())
	{
		const FStaticItemData& Data = ItemAssetDefinition->Get<FStaticItemData>();
		
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent))
		{
			StaticMeshComponent->SetStaticMesh(Data.StaticMesh);
		}
	}
}