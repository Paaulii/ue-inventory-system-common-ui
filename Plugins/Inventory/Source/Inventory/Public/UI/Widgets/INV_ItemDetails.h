#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_ItemDetails.generated.h"

class UCommonTextBlock;
class UImage;
class UINV_EquipmentViewModel;
class UINV_InventoryViewModel;
class UINV_ItemActionButton;
class UINV_ItemActionViewModel;
class UINV_ItemDetailsViewModel;
class UINV_ItemViewModel;
class UINV_SelectionViewModel;
enum class FINV_ItemActionType : uint8;

UCLASS()
class INVENTORY_API UINV_ItemDetails : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
	
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager) override;
	virtual void ClearViewModelsCache() override;
	
private:
	UFUNCTION(BlueprintCallable)
	void VM_SelectedItemUpdated(const UINV_ItemViewModel* SelectedItem);
	
	UFUNCTION(BlueprintCallable)
	void VM_OnEquipItemStateChange(const UINV_ItemViewModel* Item);
	
	UFUNCTION(BlueprintCallable)
	void OnConsumeButtonSelected();

	UFUNCTION(BlueprintCallable)
	void OnEquipButtonSelected();
	
	UFUNCTION(BlueprintCallable)
	void OnUnequipButtonSelected();
	
	UFUNCTION(BlueprintCallable)
	void OnDropButtonSelected();
	
	UFUNCTION(BlueprintCallable)
	void OnSellButtonSelected();

	void DelegateShowItemActionPopup(const FINV_ItemActionType& ActionType) const;
	void DelegatePerformItemAction(const FINV_ItemActionType& ActionType) const;
	void ToggleEquipButtonState(const UINV_ItemViewModel& SelectedItem) const;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> SelectedItemImage = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> NameText = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> DescriptionText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> ValueText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_ItemActionButton> ConsumeButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_ItemActionButton> EquipButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_ItemActionButton> UnequipButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_ItemActionButton> DropButton = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_ItemActionViewModel> CachedItemActionVM = nullptr;
};
