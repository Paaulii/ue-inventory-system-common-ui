// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_ModalConfirmationWidget.generated.h"

class UCommonTextBlock;
class UINV_ItemActionViewModel;
class UImage;
class UINV_SelectionViewModel;
class UINV_ItemViewModel;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_ModalConfirmationWidget : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_SelectedItemChanged(UINV_ItemViewModel* ItemVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_ToggleItemQuantityVisibility(bool bShouldShowQuantity);
	
	UFUNCTION(BlueprintCallable)
	void OnConfirmAction();
	
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Text_Quantity;
	
	UPROPERTY()
	TObjectPtr<UINV_ItemActionViewModel> CachedItemActionVM;

	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;
};
