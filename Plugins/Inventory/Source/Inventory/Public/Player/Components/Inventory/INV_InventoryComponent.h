// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "INV_InventoryComponent.generated.h"

class AINV_StaticMeshItem;
class AINV_SkeletalMeshItem;
class UINV_InventorySaveData;
struct FINV_ItemIdentification;
enum class FINV_ItemActionType : uint8;
class UCommonActivatableWidget;

class UINV_ModalPromptTexts;
struct FINV_ItemData;
class AINV_PlayerController;
class UINV_InventoryDataAsset;
class UINV_InventoryScreen;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UINV_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FInventoryDataChanged, const FINV_CategoryDisplayData& CategoryDisplayData);
	FInventoryDataChanged OnCategoryItemsChanged;
	
	DECLARE_DELEGATE_OneParam(FInventoryDataParsed, const FINV_InventoryDisplayData& InventoryData);
	FInventoryDataParsed OnInventoryDataParsed;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemEquipStateChanged, const FINV_ItemIdentification&, ItemIdentification);
	FItemEquipStateChanged OnItemEquipped;
	FItemEquipStateChanged OnItemUnequipped;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateModifyEffects, const TArray<TSubclassOf<UGameplayEffect>>&, Effects);
	FDelegateModifyEffects OnDelegateApplyEffect;
	FDelegateModifyEffects OnDelegateRevokeEffect;
	
	void ToggleInventory();
	void TryAddItem(const FINV_ItemData& ItemData);
	FText GetPromptTextByActionType(const FINV_ItemActionType& ActionType) const;
	void ShowItemActionPopup() const;
	void PerformAction(const FINV_ItemActionType& ActionType,  const FINV_ItemIdentification& ItemId, const int32 Amount);
	void LoadInventoryData();

	FINV_ItemAssetDefinition* GetItemAssetDefinition(const FINV_ItemIdentification& ItemId) const;
protected:
	virtual void BeginPlay() override;
private:
	void DropItem(const FINV_ItemIdentification& ItemId, const int16 Amount = 1);
	void EquipItems();
	void ConsumeItem(const FINV_ItemIdentification& ItemId, const int16 Amount = 1);
	bool DecreaseItemQuantity(const FINV_ItemIdentification& ItemId, const int16 Amount);
	void TryEquipItem(const FINV_ItemIdentification& ItemIdentification);
	void EquipItem(const FINV_ItemIdentification& ItemIdentification) const;
	void TryUnequipItem(const FINV_ItemIdentification& ItemIdentification );
	void UnequipItemAt(const int32 IndexToUnequip);
	void SetInventoryVisible(bool bIsVisible);
	void RequestShowInventory();
	void SaveInventoryData(const TArray<FINV_ItemData>& DataToSave) const;
	void SaveEquipPlayerItems(const TArray<FINV_ItemIdentification>& EquippedItemsToSave) const;
	void UpdateDisplayInventoryDataEntry(const FINV_ItemData& ItemData);
	void DelegateApplyEffects(const FINV_ItemIdentification& ItemId) const;
	int32 GetNextGUID() const;
	FINV_ItemData* GetCachedItem(int16 ItemUID);
	
	TOptional<FINV_ItemDisplayData> CreateItemDisplayData(const FINV_ItemData& ItemDefinition) const;
	TArray<FINV_CategoryDisplayData> TranslatePlayerItemsToDisplayData ();
	FINV_ItemData* GetCachedItemBy(int16 ItemId);


	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UINV_InventoryScreen> InventoryClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory" )
	TObjectPtr<UINV_InventoryDataAsset> InventoryDataAsset;
	
	// TODO: Move it to a separate DataAssets for Inventory Settings
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Settings")
	int32 DefaultInventoryCapacity;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items" )
	TSubclassOf<AINV_SkeletalMeshItem> SkeletalMeshItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items" )
	TSubclassOf<AINV_StaticMeshItem> StaticMeshItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items" )
	float DropItemRadius;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items" )
	float DropItemHeight;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory/Modal" )
	TObjectPtr<UINV_ModalPromptTexts> ModalPromptTextsData;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory/Modal" )
	TSubclassOf<UCommonActivatableWidget> ModalClass;
	
	TWeakObjectPtr<AINV_PlayerController> OwningController;
	
	TArray<FINV_ItemData> CachedPlayerItems {};
	TArray<FINV_ItemIdentification> EquippedItems {};
	FINV_InventoryDisplayData CachedInventoryDisplayData {};
	
	bool bIsBindToInventoryOnDeactivated;
	bool bInventoryMenuOpen;
};
