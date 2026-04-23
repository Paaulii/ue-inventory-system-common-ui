#pragma once

#include "CoreMinimal.h"
#include "INV_ItemViewModel.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_SelectionViewModel.generated.h"

UCLASS()
class INVENTORY_API UINV_SelectionViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetSelectedCategory(UINV_CategoryViewModel* Category);

	UFUNCTION(BlueprintCallable)
	void SetSelectedItem(UINV_ItemViewModel* ItemVM);
	
	UFUNCTION(BlueprintCallable)
	void TryRequestRefreshFocusTarget();
	
	UINV_CategoryViewModel* GetSelectedCategory() const { return SelectedCategory; }
	const UINV_ItemViewModel* GetSelectedItem() const { return SelectedItem; }
	bool GetbRefreshFocusRequested() const { return bRefreshFocusRequested; }

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool bRefreshFocusRequested = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	TObjectPtr<UINV_CategoryViewModel> SelectedCategory = nullptr;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	TObjectPtr<UINV_ItemViewModel> SelectedItem = nullptr;
};
