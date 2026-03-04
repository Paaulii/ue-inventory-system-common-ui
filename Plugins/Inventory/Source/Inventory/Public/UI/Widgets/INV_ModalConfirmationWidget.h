// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_ModalConfirmationWidget.generated.h"

class UINV_PromptViewModel;
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
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY()
	TObjectPtr<UINV_PromptViewModel> CachedPromptVM;

	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;
};
