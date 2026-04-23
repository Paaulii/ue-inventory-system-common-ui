#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_ModalConfirmationWidget.generated.h"

class UCommonTextBlock;
class UINV_ItemActionViewModel;
class UINV_ItemViewModel;
class UINV_SelectionViewModel;
class UImage;

UCLASS()
class INVENTORY_API UINV_ModalConfirmationWidget : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()

protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager) override;
	virtual void ClearViewModelsCache() override;
	
private:
	UFUNCTION(BlueprintCallable)
	void VM_SelectedItemChanged(const UINV_ItemViewModel* ItemVM);
	
	UFUNCTION(BlueprintCallable)
	void OnConfirmAction();
	
	UFUNCTION(BlueprintCallable)
	void VM_ToggleItemQuantityVisibility(bool bIsSingleItemQuantityAction);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ImageIcon = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_ItemActionViewModel> CachedItemActionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;
};
