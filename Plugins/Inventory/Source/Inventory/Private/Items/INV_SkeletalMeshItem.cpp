// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_SkeletalMeshItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"


AINV_SkeletalMeshItem::AINV_SkeletalMeshItem()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
}

void AINV_SkeletalMeshItem::ChangeMesh(TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition)
{
	if (ItemAssetDefinition->GetScriptStruct() == FSkeletalItemData::StaticStruct())
	{
		const FSkeletalItemData& Data = ItemAssetDefinition->Get<FSkeletalItemData>();
		if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent))
		{
			SkeletalMeshComponent->SetSkeletalMesh(Data.SkeletalMesh);
			SkeletalMeshComponent->SetMaterial(0, Data.Material);
		}
	}
}

