// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_StaticEquippedItem.h"

#include "Data/Types/INV_InventoryDataAssetTypes.h"


// Sets default values
AINV_StaticEquippedItem::AINV_StaticEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetActorEnableCollision(false);
}

void AINV_StaticEquippedItem::SetMesh(const TInstancedStruct<FINV_ItemAssetDefinition>* ItemDefinition) const
{
	if (ItemDefinition->GetScriptStruct() == FStaticItemData::StaticStruct())
	{
		const FStaticItemData& Data = ItemDefinition->Get<FStaticItemData>();
		StaticMeshComponent->SetStaticMesh(Data.StaticMesh);
	}
}
