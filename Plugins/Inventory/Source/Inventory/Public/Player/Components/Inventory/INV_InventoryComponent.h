// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "INV_InventoryComponent.generated.h"

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
	DECLARE_DELEGATE_OneParam(FInventoryDataChanged, const FINV_InventoryDisplayData& InventoryData);
	FInventoryDataChanged OnInventoryDataChanged;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateApplyEffect, const TArray<TSubclassOf<UGameplayEffect>>&, Effects);
	FDelegateApplyEffect OnDelegateApplyEffect;
	
	void ToggleInventory();
	void TryAddItem(FINV_ItemData& ItemData);
	FText GetPromptTextByActionType(const FINV_ItemActionType& ActionType) const;
	void ShowItemActionPopup() const;
	void PerformAction(const FINV_ItemActionType& ActionType,  const FINV_ItemIdentification& ItemId, const int32 Amount);
protected:
	virtual void BeginPlay() override;
	void LoadInventoryData();
private:
	void ConsumeItem(const FINV_ItemIdentification& ItemId, const int16 Amount = 1);
	void SetInventoryVisible(bool bIsVisible);
	void RequestShowInventory();
	void SaveInventoryData(const TArray<FINV_ItemData>& DataToSave) const;
	void UpdateDisplayInventoryDataEntry(const FINV_ItemData& ItemData);
	void DelegateApplyEffects(const FINV_ItemIdentification& ItemId) const;
	int32 GetNextGUID() const;
	FINV_ItemData* GetCachedItem(int16 ItemUID);
	
	TOptional<FINV_ItemDisplayData> CreateItemDisplayData(const FINV_ItemData& ItemDefinition) const;
	TArray<FINV_CategoryDisplayData> TranslatePlayerItemsToDisplayData (TArray<FINV_ItemData>& PlayerItemDataList) const;
	FINV_ItemData* GetCachedItemBy(int16 ItemUID);
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UINV_InventoryScreen> InventoryClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory" )
	TObjectPtr<UINV_InventoryDataAsset> InventoryDataAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory/Modal" )
	TObjectPtr<UINV_ModalPromptTexts> ModalPromptTextsData;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory/Modal" )
	TSubclassOf<UCommonActivatableWidget> ModalClass;
	
	TWeakObjectPtr<AINV_PlayerController> OwningController;
	
	TArray<FINV_ItemData> CachedPlayerItems;
	FINV_InventoryDisplayData CachedInventoryDisplayData;
	
	bool bIsBindToInventoryOnDeactivated;
	bool bInventoryMenuOpen;
};
