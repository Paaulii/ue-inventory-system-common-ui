#include "Items/INV_SkeletalEquippedItem.h"
#include "Data/Types/INV_InventoryDataAssetTypes.h"

AINV_SkeletalEquippedItem::AINV_SkeletalEquippedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneRoot);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SetActorEnableCollision(false);
}

void AINV_SkeletalEquippedItem::SetMesh(const FINV_ItemAssetDefinition* ItemDefinition, USkeletalMeshComponent* ParentMeshComponent) const
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

			if (ParentMeshComponent && ParentMeshComponent->GetAnimInstance())
			{
				if (UClass* AnimClass = ParentMeshComponent->GetAnimInstance()->GetClass())
				{
					SkeletalMeshComponent->SetAnimInstanceClass(AnimClass);
				}

				if (USkinnedMeshComponent* SkinnedMeshComponent = Cast<USkinnedMeshComponent>(ParentMeshComponent))
				{
					SkeletalMeshComponent->SetLeaderPoseComponent(SkinnedMeshComponent);
				}
			}
		}
	}
}