#include "Items/INV_Item.h"
#include "Data/INV_InventoryDataAsset.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"
#include "GameFramework/RotatingMovementComponent.h"

AINV_Item::AINV_Item()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneRoot);
	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(FName("RotatingComponent"));
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

void AINV_Item::Highlight()
{
	MeshComponent->SetOverlayMaterial(HighlightMaterial);
}

void AINV_Item::Unhighlight()
{
	MeshComponent->SetOverlayMaterial(nullptr);
}

#if WITH_EDITOR
void AINV_Item::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.MemberProperty != NULL)? PropertyChangedEvent.MemberProperty->GetFName(): NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AINV_Item, ItemData))
	{
		if (ItemData.ItemIdentification.ItemTag.IsValid() && ItemData.ItemIdentification.CategoryTag.IsValid())
		{
			SetupMesh();
		}
	}
}
#endif

void AINV_Item::Initialize(const FINV_ItemData& Data)
{
	ItemData = Data;
	Setup();
}

void AINV_Item::Setup()
{
	if (MeshComponent)
	{
		SetupMesh();
	}
}

void AINV_Item::SetupMesh()
{
	FINV_ItemAssetDefinition* ItemAssetDefinition = InventoryDataAsset->GetItemAssetDefinition(ItemData.ItemIdentification.ItemTag,
		ItemData.ItemIdentification.CategoryTag);

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