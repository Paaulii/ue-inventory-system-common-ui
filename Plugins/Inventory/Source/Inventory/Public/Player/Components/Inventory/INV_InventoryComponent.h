// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Types/INV_InventoryDisplayTypes.h"
#include "INV_InventoryComponent.generated.h"

class AINV_PlayerController;
class UINV_InventoryDataAsset;
struct FINV_ItemSaveData;
class UINV_InventoryScreen;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UINV_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FInventoryDataChanged, const FINV_InventoryDisplayData& InventoryData);
	FInventoryDataChanged OnInventoryDataChanged;
	
	void ToggleInventory();

protected:
	virtual void BeginPlay() override;
	void LoadInventoryData();
	void SaveItemToInventoryData(FINV_ItemSaveData& ItemData);

private:
	void SetInventoryVisible(bool bIsVisible);
	void RequestShowInventory();
	TArray<FINV_CategoryDisplayData> TranslatePlayerItemsToDisplayData (const TArray<FINV_ItemSaveData>& PlayerItemDataList);
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UINV_InventoryScreen> InventoryClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory" )
	TObjectPtr<UINV_InventoryDataAsset> InventoryDataAsset;

	FINV_InventoryDisplayData CachedInventoryData;
	TWeakObjectPtr<AINV_PlayerController> OwningController;
	
	bool bIsBindToInventoryOnDeactivated;
	bool bInventoryMenuOpen;
};
