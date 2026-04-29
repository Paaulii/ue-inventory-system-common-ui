#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_CategoryItems.generated.h"

class UDynamicEntryBox;
class UINV_CategoryViewModel;
class UINV_InputAction;
class UINV_InventoryViewModel;
class UINV_ItemTile;
class UINV_ItemViewModel;
class UINV_SelectionViewModel;
class UMVVMView;

UCLASS()
class INVENTORY_API UINV_CategoryItems : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager) override;

private:
	UFUNCTION(BlueprintCallable)
	void VM_CategoryItemsChanged(const TArray<UINV_ItemViewModel*>& ItemsVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_SelectedCategoryChanged(UINV_CategoryViewModel* CategoryVM);

	UFUNCTION(BlueprintCallable)
	void VM_ForceFocusEvaluation(bool bHasPendingRequest);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FText VM_GetItemsCapacityText(const UINV_ItemViewModel* ItemVM) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UUserWidget* GetFocusTile() const;
	
	UFUNCTION(BlueprintCallable)
	void ChangePage(int32 PageOffset);
	
	void PopulateSlots();
	UINV_ItemTile* CreateSlot();
	void UpdateSlots(TArray<UINV_ItemViewModel*> ItemViewModels);
	void UpdatePageButtonVisibility();
	void SelectFirstItemOnPage();
	int GetItemIndexForSelectedCategory() const;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxDynamicEntryBoxCapacity = 0;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBoxItems = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_InputAction> PreviousPageInputAction = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_InputAction> NextPageInputAction = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_CategoryViewModel> CachedCategoryVM = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CachedInventoryVM = nullptr;

	UPROPERTY()
	TArray<UINV_ItemTile*> ItemTiles = {};
	
	UPROPERTY()
	TArray<UINV_ItemViewModel*> CachedItemsVM = {};
	
	int32 CurrentPage = 0;
	int32 PageCount = 1;
};
