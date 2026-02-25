// Copyright Paulina Hałatek, All Rights Reserved.


#include "Items/INV_Item.h"
#include "Data/INV_InventoryDataAsset.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"
#include "GameFramework/RotatingMovementComponent.h"

AINV_Item::AINV_Item()
{
	PrimaryActorTick.bCanEverTick = false;
	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingComponent");
}

void AINV_Item::BeginPlay()
{
	Super::BeginPlay();
	Setup();
}

void AINV_Item::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Setup();
}

void AINV_Item::Highlight_Implementation()
{
	MeshComponent->SetOverlayMaterial(HighlightMaterial);
}

void AINV_Item::UnHighlight_Implementation()
{
	MeshComponent->SetOverlayMaterial(nullptr);
}

#if WITH_EDITOR
void AINV_Item::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.MemberProperty != NULL)
		                     ? PropertyChangedEvent.MemberProperty->GetFName()
		                     : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AINV_Item, ItemDefinition))
	{
		if (ItemDefinition.ItemId >= 0 && ItemDefinition.CategoryId >= 0)
		{
			SetupMesh();
		}
	}
}
#endif

void AINV_Item::SetupMesh()
{
	TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition = InventoryDataAsset->GetInstancedItemDefinition(
		ItemDefinition.ItemId, ItemDefinition.CategoryId);

	if (!ItemAssetDefinition)
	{
		return;
	}

	ChangeMesh(ItemAssetDefinition);
}

void AINV_Item::PickUp()
{
	Destroy();
}

void AINV_Item::Setup()
{
	if (MeshComponent)
	{
		SetupMesh();
	}
}
