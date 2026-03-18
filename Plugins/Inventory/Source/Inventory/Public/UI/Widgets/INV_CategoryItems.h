// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_CategoryItems.generated.h"

class UINV_InputAction;
class UINV_ItemTile;
class UINV_InventoryViewModel;
class UDynamicEntryBox;
class UINV_CategoryViewModel;
class UMVVMView;
class UINV_ItemViewModel;
class UINV_SelectionViewModel;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_CategoryItems : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
protected:
	UFUNCTION(BlueprintCallable)
	void VM_ForceFocusEvaluation(bool bHasPendingRequest);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText VM_GetItemsCapacityText(UINV_ItemViewModel* ItemVM) const;
	
	UFUNCTION(BlueprintCallable)
	void VM_CategoryItemsChanged(TArray<UINV_ItemViewModel*> ItemsVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_SelectedCategoryChanged(UINV_CategoryViewModel* CategoryVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_RefreshFocusTarget(TArray<UINV_ItemViewModel*> ItemsVM);
	
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
	TObjectPtr<UINV_InputAction> InputAction_PreviousPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_InputAction> InputAction_NextPage;
private:
	void UpdateSlots(TArray<UINV_ItemViewModel*> ItemViewModels);
	void PopulateSlots();
	void UpdatePageButtonVisibility();
	UINV_ItemTile* CreateSlot();
	int GetItemIndexForSelectedCategory() const;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;

	UPROPERTY()
	TObjectPtr<UINV_CategoryViewModel> CachedCategoryVM;
	
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CachedInventoryVM;

	UPROPERTY()
	TArray<UINV_ItemTile*> ItemTiles;
	
	UPROPERTY()
	TArray<UINV_ItemViewModel*> CachedItemsVM;
	
	int CurrentPage = 0;
	int PageCount = 1;
};
