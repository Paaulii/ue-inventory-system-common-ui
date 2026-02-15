// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ItemViewModel.h"
#include "MVVMViewModelBase.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_SelectionViewModel.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_SelectionViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	UINV_CategoryViewModel* GetSelectedCategory() const { return SelectedCategory; }
	UINV_ItemViewModel* GetSelectedItem() const { return SelectedItem; }
	bool GetRefreshFocusRequested() const { return RefreshFocusRequested; }
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedCategory(UINV_CategoryViewModel* Category);

	UFUNCTION(BlueprintCallable)
	void SetSelectedItem(UINV_ItemViewModel* ItemVM);
	
	UFUNCTION(BlueprintCallable)
	void TryRequestRefreshFocusTarget();

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool RefreshFocusRequested;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	UINV_CategoryViewModel* SelectedCategory;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	UINV_ItemViewModel* SelectedItem;
};
