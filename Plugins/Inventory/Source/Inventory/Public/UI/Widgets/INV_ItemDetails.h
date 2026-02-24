// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_ItemDetails.generated.h"

class UINV_ItemViewModel;
class UImage;
class UINV_SelectionViewModel;
class UMVVMView;

class UCommonTextBlock;
UCLASS()
class INVENTORY_API UINV_ItemDetails : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_SelectedItemUpdated(UINV_ItemViewModel* SelectedItem);
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_SelectedItem;
	
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* Text_Name;
	
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* Text_Description;

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* Text_Value;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;
	
};
