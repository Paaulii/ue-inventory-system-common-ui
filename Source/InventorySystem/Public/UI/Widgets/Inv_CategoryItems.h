// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inv_ActivatableMvvmWidget.h"
#include "Inv_CategoryItems.generated.h"

class UItemTile;
class UInventoryViewModel;
class UDynamicEntryBox;
class UCategoryViewModel;
class UMVVMView;
class UItemViewModel;
class USelectionViewModel;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInv_CategoryItems : public UInv_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void CacheViewModels(UUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
protected:
	UFUNCTION(BlueprintCallable)
	void VM_ForceFocusEvaluation(bool bHasPendingRequest);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText VM_GetItemsCapacityText(TArray<UItemViewModel*> ItemsVM) const;
	
	UFUNCTION(BlueprintCallable)
	void VM_UpdateSlots(TArray<UItemViewModel*> ItemsVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_SelectedCategoryChanged(UCategoryViewModel* CategoryVM);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UUserWidget* GetFocusTile() const;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Items;

	UPROPERTY(EditDefaultsOnly)
	int MaxDynamicEntryBoxCapacity;
private:
	/**
	 * Function used for refreshing focus target when first tile is ready - when it's selection state animation is finished
	 *
	 * @param ItemTile  First item tile that is currently selected 
	 */
	UFUNCTION()
	void OnItemTileReady(UItemTile* ItemTile);
	
	void PopulateSlots();
	UItemTile* CreateSlot();
	int GetItemIndexForSelectedCategory() const;
	
	UPROPERTY()
	TObjectPtr<USelectionViewModel> CachedSelectionVM;

	UPROPERTY()
	TObjectPtr<UCategoryViewModel> CachedCategoryVM;
	
	UPROPERTY()
	TObjectPtr<UInventoryViewModel> CachedInventoryVM;

	UPROPERTY()
	TArray<UItemTile*> ItemTiles;
};
