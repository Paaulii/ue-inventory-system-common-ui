#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "INV_InventoryComponent.generated.h"

class AINV_PlayerController;
class AINV_SkeletalMeshItem;
class AINV_StaticMeshItem;
class UCommonActivatableWidget;
class UINV_InventoryDataAsset;
class UINV_InventorySaveData;
class UINV_InventoryScreen;
class UINV_ModalPromptTexts;
enum class FINV_ItemActionType : uint8;
struct FINV_ItemData;
struct FINV_ItemIdentification;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UINV_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FINV_InventoryDataChanged, const FINV_CategoryDisplayData& CategoryDisplayData);
	FINV_InventoryDataChanged OnCategoryItemsChanged;
	
	DECLARE_DELEGATE_OneParam(FINV_InventoryDataParsed, const FINV_InventoryDisplayData& InventoryData);
	FINV_InventoryDataParsed OnInventoryDataParsed;
	
	DECLARE_DELEGATE_OneParam(FINV_ItemCollected, FINV_ItemData& ItemData);
	FINV_ItemCollected OnItemCollected;
	
	DECLARE_DELEGATE_OneParam(FINV_CurrencyChanged, const int32 Value);
	FINV_CurrencyChanged OnCurrencyChanged;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FINV_ItemEquipStateChanged, const FINV_ItemIdentification&, ItemIdentification);
	FINV_ItemEquipStateChanged OnItemEquipped;
	FINV_ItemEquipStateChanged OnItemUnequipped;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FINV_DelegateModifyEffects, const TArray<TSubclassOf<UGameplayEffect>>&, Effects);
	FINV_DelegateModifyEffects OnDelegateApplyEffect;
	FINV_DelegateModifyEffects OnDelegateRevokeEffect;

	virtual void BeginPlay() override;
	void LoadInventoryData();
	void ToggleInventory();
	void TryAddItem(const FINV_ItemData& ItemData);
	void PerformAction(const FINV_ItemActionType& ActionType,  const FINV_ItemIdentification& ItemId, const int32 Amount);
	void ShowItemActionPopup() const;
	const FText& GetPromptTextByActionType(const FINV_ItemActionType& ActionType) const;
	FINV_ItemAssetDefinition* GetItemAssetDefinition(const FINV_ItemIdentification& ItemId) const;
	TOptional<FINV_ItemDisplayData> CreateItemDisplayData(const FINV_ItemData& ItemData) const;
	
private:
	void SetInventoryVisible(bool bIsVisible);
	void RequestShowInventory();
	void DropItem(const FINV_ItemIdentification& ItemId, const int32 Amount);
	void ConsumeItem(const FINV_ItemIdentification& ItemId, const int32 Amount);
	void TryEquipItem(const FINV_ItemIdentification& ItemIdentification);
	void EquipItem(const FINV_ItemIdentification& ItemIdentification) const;
	void EquipItems();
	void TryUnequipItem(const FINV_ItemIdentification& ItemIdentification);
	void UnequipItemAt(const int32 IndexToUnequip);
	void SellItem(const FINV_ItemIdentification& ItemId, const int32 Amount);
	void SaveInventoryData(const TArray<FINV_ItemData>& DataToSave) const;
	void SaveEquipPlayerItems(const TArray<FINV_ItemIdentification>& EquippedItemsToSave) const;
	void UpdateDisplayInventoryDataEntry(const FINV_ItemData& ItemData);
	void DelegateApplyEffects(const FINV_ItemIdentification& ItemId) const;
	void NotifyItemCollected(FINV_ItemData ItemData, int32 ItemUID) const;
	bool DecreaseItemQuantity(const FINV_ItemIdentification& ItemId, const int32 Amount);
	int32 GetNextUID() const;
	FINV_ItemData* GetCachedItem(int32 ItemUID);
	TArray<FINV_CategoryDisplayData> TranslatePlayerItemsToDisplayData();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UINV_InventoryScreen> InventoryClass = {}; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UINV_InventoryDataAsset> InventoryDataAsset = nullptr;
	
	// TODO: Move it to a separate DataAssets for Inventory Settings
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Settings")
	int32 DefaultInventoryCapacity = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items")
	TSubclassOf<AINV_SkeletalMeshItem> SkeletalMeshItemClass = {};

	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items")
	TSubclassOf<AINV_StaticMeshItem> StaticMeshItemClass = {};

	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items")
	float DropItemRadius = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Dropping Items" )
	float DropItemHeight = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Modal" )
	TObjectPtr<UINV_ModalPromptTexts> ModalPromptTextsData = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory | Modal" )
	TSubclassOf<UCommonActivatableWidget> ModalClass = {};
	
	TWeakObjectPtr<AINV_PlayerController> OwningController = nullptr;
	
	TArray<FINV_ItemData> CachedPlayerItems = {};
	TArray<FINV_ItemIdentification> EquippedItems  = {};
	FINV_InventoryDisplayData CachedInventoryDisplayData = {};
	
	bool bIsBindToInventoryOnDeactivated = false;
	bool bInventoryMenuOpen = false;
};
