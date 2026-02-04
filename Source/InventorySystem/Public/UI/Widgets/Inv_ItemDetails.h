// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Inv_ActivatableMvvmWidget.h"
#include "Inv_ItemDetails.generated.h"

class UImage;
class USelectionViewModel;
class UMVVMView;
/**
 * 
 */
 // TODO: This will be definite convention for files, 
 // for now I leave the rest of the files, but at the end of implementing Inventory System I will fix their naming.
UCLASS()
class INVENTORYSYSTEM_API UInv_ItemDetails : public UInv_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_SelectedItemImageUpdated(UTexture2D* Image);
protected:
	virtual void CacheViewModels(UUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_SelectedItem;
	
	UPROPERTY()
	TObjectPtr<USelectionViewModel> CachedSelectionVM;
	
};
