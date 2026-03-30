// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/INV_ProxyMesh.h"
#include "INV_EquipmentComponent.generated.h"


class AINV_StaticEquippedItem;
class AINV_SkeletalEquippedItem;
struct FINV_ItemIdentification;
class UINV_InventoryComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UINV_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemEquipStateChanged, AActor*, Item);
	FItemEquipStateChanged OnItemAttached;
	FItemEquipStateChanged OnItemDetached;
	
	UINV_EquipmentComponent();
	void BindToInventoryComponentEquipEvents();
	void Initialize(APlayerController* Controller, USkeletalMeshComponent* Mesh );
	void SetOwningMesh(USkeletalMeshComponent* Mesh);
private:
	AActor* SpawnEquippedItem(const FINV_ItemIdentification& ItemId);
	
	UFUNCTION()
	void OnItemEquipped(const FINV_ItemIdentification& EquippedItem);
	
	UFUNCTION()
	void OnItemUnequipped(const FINV_ItemIdentification& UnequippedItem);
	
	UFUNCTION()
	void ResetOwningMesh(APawn* OldPawn, APawn* NewPawn);
	
	UPROPERTY()
	TMap<int32, AActor*> EquippedItems;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AINV_SkeletalEquippedItem> SkeletalEquippedItemClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AINV_StaticEquippedItem> StaticEquippedItemClass;

	TWeakObjectPtr<UINV_InventoryComponent> InventoryComponent;
	TWeakObjectPtr<APlayerController> OwningPlayerController;
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwningSkeletalMesh;
};
