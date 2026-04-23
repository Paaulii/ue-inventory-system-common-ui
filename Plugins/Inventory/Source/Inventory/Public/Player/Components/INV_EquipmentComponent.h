#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "INV_EquipmentComponent.generated.h"

class AINV_SkeletalEquippedItem;
class AINV_StaticEquippedItem;
class UINV_InventoryComponent;
struct FINV_ItemIdentification;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UINV_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FINV_ItemEquipStateChanged, AActor*, Item);
	FINV_ItemEquipStateChanged OnItemAttached;
	FINV_ItemEquipStateChanged OnItemDetached;
	
	UINV_EquipmentComponent();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Initialize(APlayerController* Controller, USkeletalMeshComponent* Mesh);
	void SetOwningMesh(USkeletalMeshComponent* Mesh);
private:
	UFUNCTION()
	void OnItemEquipped(const FINV_ItemIdentification& EquippedItem);
	
	UFUNCTION()
	void OnItemUnequipped(const FINV_ItemIdentification& UnequippedItem);
	
	UFUNCTION()
	void ResetOwningMesh(APawn* OldPawn, APawn* NewPawn);
	
	void BindToInventoryComponentEquipEvents();
	AActor* SpawnEquippedItem(const FINV_ItemIdentification& ItemId);
	
	UPROPERTY()
	TMap<int32, AActor*> EquippedItems = {};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AINV_SkeletalEquippedItem> SkeletalEquippedItemClass = {};
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AINV_StaticEquippedItem> StaticEquippedItemClass = {};

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwningSkeletalMesh = nullptr;
	
	TWeakObjectPtr<UINV_InventoryComponent> InventoryComponent = nullptr;
	TWeakObjectPtr<APlayerController> OwningPlayerController = nullptr;
};
