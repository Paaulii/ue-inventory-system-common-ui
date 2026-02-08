// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_ItemDetails.generated.h"

class UImage;
class UINV_SelectionViewModel;
class UMVVMView;
/**
 * 
 */
 // TODO: This will be definite convention for files, 
 // for now I leave the rest of the files, but at the end of implementing Inventory System I will fix their naming.
UCLASS()
class INVENTORY_API UINV_ItemDetails : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_SelectedItemImageUpdated(UTexture2D* Image);
protected:
	virtual void CacheViewModels(UINV_UIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_SelectedItem;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;
	
};
