// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inv_ActivatableMvvmWidget.h"
#include "Inv_CategoryItems.generated.h"

class UInv_InputAction;
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
	FText VM_GetItemsCapacityText(UItemViewModel* ItemVM) const;
	
	UFUNCTION(BlueprintCallable)
	void VM_CategoryItemsChanged(TArray<UItemViewModel*> ItemsVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_SelectedCategoryChanged(UCategoryViewModel* CategoryVM);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UUserWidget* GetFocusTile() const;
	void SelectFirstItemOnPage();

	UFUNCTION(BlueprintCallable)
	void ChangePage(int PageOffset);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Items;

	UPROPERTY(EditDefaultsOnly)
	int MaxDynamicEntryBoxCapacity;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InputAction> InputAction_PreviousPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InputAction> InputAction_NextPage;
private:
	/**
	 * Function used for refreshing focus target when first tile is ready - when it's selection state animation is finished
	 *
	 * @param ItemTile  First item tile that is currently selected 
	 */
	UFUNCTION()
	void OnItemTileReady(UItemTile* ItemTile);

	void UpdateSlots(TArray<UItemViewModel*> ItemViewModels);
	void PopulateSlots();
	void UpdatePageButtonVisibility();
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
	
	UPROPERTY()
	TArray<UItemViewModel*> CachedItemsVM;
	
	int CurrentPage = 0;
	int PageCount = 1;
};
