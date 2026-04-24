#include "Player/Components/INV_EquipmentComponent.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "GameFramework/Character.h"
#include "Items/INV_StaticEquippedItem.h"
#include "Items/INV_SkeletalEquippedItem.h"
#include "Items/Interaction/INV_Equippable.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"
#include "Utils/INV_InventoryStatics.h"

UINV_EquipmentComponent::UINV_EquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UINV_EquipmentComponent::Initialize(APlayerController* Controller, USkeletalMeshComponent* Mesh)
{
	if (ensureMsgf(Controller, TEXT("Passed PlayerController for equipment component is null!")))
	{
		OwningPlayerController = Controller;

		if (Mesh)
		{
			SetOwningMesh(Mesh);
		}
		else if (ACharacter* OwnerCharacter = Cast<ACharacter>(OwningPlayerController->GetCharacter()))
		{
			SetOwningMesh(OwnerCharacter->GetMesh());
		}

		OwningPlayerController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::ResetOwningMesh);
	}

	BindToInventoryComponentEquipEvents();
}

void UINV_EquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (OwningPlayerController != nullptr)
	{
		OwningPlayerController->OnPossessedPawnChanged.RemoveAll(this);
	}
}

void UINV_EquipmentComponent::SetOwningMesh(USkeletalMeshComponent* Mesh)
{
	OwningSkeletalMesh = Mesh;
}

void UINV_EquipmentComponent::BindToInventoryComponentEquipEvents()
{
	InventoryComponent = UINV_InventoryStatics::GetInventoryComponent(OwningPlayerController.Get());

	if (!InventoryComponent.IsValid())
	{
		return;
	}

	if (!InventoryComponent->OnItemEquipped.IsAlreadyBound(this, &UINV_EquipmentComponent::OnItemEquipped))
	{
		InventoryComponent->OnItemEquipped.AddDynamic(this, &UINV_EquipmentComponent::OnItemEquipped);
	}

	if (!InventoryComponent->OnItemUnequipped.IsAlreadyBound(this, &UINV_EquipmentComponent::OnItemUnequipped))
	{
		InventoryComponent->OnItemUnequipped.AddDynamic(this, &UINV_EquipmentComponent::OnItemUnequipped);
	}
}

void UINV_EquipmentComponent::OnItemEquipped(const FINV_ItemIdentification& EquippedItem)
{
	if (AActor* AttachedItem = SpawnEquippedItem(EquippedItem))
	{
		OnItemAttached.Broadcast(AttachedItem);
	}
}

void UINV_EquipmentComponent::OnItemUnequipped(const FINV_ItemIdentification& UnequippedItem)
{
	if (!EquippedItems.Contains(UnequippedItem.Id))
	{
		return;
	}
	
	if (AActor* SpawnedItem = EquippedItems[UnequippedItem.Id])
	{
		OnItemDetached.Broadcast(SpawnedItem);
		SpawnedItem->Destroy();
		EquippedItems.Remove(UnequippedItem.Id);
	}
}

AActor* UINV_EquipmentComponent::SpawnEquippedItem(const FINV_ItemIdentification& ItemId)
{
	if (UWorld* World = GetWorld())
	{
		FINV_ItemAssetDefinition* ItemAssetDefinition = InventoryComponent->GetItemAssetDefinition(ItemId);

		if (!ensureMsgf(ItemAssetDefinition, TEXT("Couldn't find item's asset definition. Check if InventoryDataAsset contains item with tag %s"), *ItemId.ItemTag.ToString()))
		{
			return nullptr;
		}
		
		AActor* SpawnedEquippedItem = nullptr;

		if (ItemAssetDefinition->SkeletalMesh && SkeletalEquippedItemClass)
		{
			SpawnedEquippedItem = World->SpawnActor(SkeletalEquippedItemClass.Get());
		}
		else if (ItemAssetDefinition->StaticMesh && StaticEquippedItemClass)
		{
			SpawnedEquippedItem = World->SpawnActor(StaticEquippedItemClass.Get());
		}

		if (!SpawnedEquippedItem)
		{
			return nullptr;
		}
		
		if (IINV_Equippable* EquippableItem = Cast<IINV_Equippable>(SpawnedEquippedItem))
		{
			EquippableItem->SetMesh(ItemAssetDefinition);
			EquippedItems.Add(ItemId.Id, SpawnedEquippedItem);
			SpawnedEquippedItem->AttachToComponent(OwningSkeletalMesh, FAttachmentTransformRules:: SnapToTargetNotIncludingScale, ItemAssetDefinition->SocketAttachPoint);
			return SpawnedEquippedItem;
		}
	}

	return nullptr;
}

void UINV_EquipmentComponent::ResetOwningMesh(APawn* OldPawn, APawn* NewPawn)
{
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(NewPawn))
	{
		SetOwningMesh(OwnerCharacter->GetMesh());
	}
}

