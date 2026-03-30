// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_SkeletalEquippedItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"


AINV_SkeletalEquippedItem::AINV_SkeletalEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetActorEnableCollision(false);
}

void AINV_SkeletalEquippedItem::SetMesh(const TInstancedStruct<FINV_ItemAssetDefinition>* ItemDefinition) const
{
	if (ItemDefinition->GetScriptStruct() == FSkeletalItemData::StaticStruct())
	{
		const FSkeletalItemData& Data = ItemDefinition->Get<FSkeletalItemData>();
		SkeletalMeshComponent->SetSkeletalMesh(Data.SkeletalMesh);
		SkeletalMeshComponent->SetMaterial(0, Data.Material);
	}
}

